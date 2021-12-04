//
//  ScriptingParser.cpp
//  ScriptingEngine
//
//  Created by Jeppe Nielsen on 19/10/2021.
//

#include "ScriptingParser.hpp"
#include <clang-c/Index.h>
#include <iostream>
#include <set>
#include <map>
#include <dirent.h>
#include <sstream>

using namespace Tiny;

CXChildVisitResult parseCode(CXCursor cursor, CXCursor parent, CXClientData clientData);

ScriptingParser::ScriptingParser(const std::string& clangPath) : clangLocation(clangPath) {
    
}

bool ScriptingParser::Parse(const ScriptingContext& context, const std::function<bool(const std::string&)>& predicate, ScriptingParserResult& result) {
    
    std::vector<std::string> contextArguments = GetArguments(context);
    
    std::vector<const char*> arguments;
    
    for(auto& contextArgument : contextArguments) {
        arguments.push_back(contextArgument.c_str());
    }
    
    for(auto cppFile : context.cppFiles) {
        CXIndex index = clang_createIndex(0,1);

        // create Translation Unit
        CXTranslationUnit tu = clang_parseTranslationUnit(index, cppFile.c_str(), &arguments[0], (int)arguments.size(), NULL, 0,
                                            CXTranslationUnit_KeepGoing | CXTranslationUnit_Incomplete);
        
        if (tu == NULL) {
            printf("Cannot parse translation unit\n");
            return false;
        }

        CXCursor startCursor = clang_getTranslationUnitCursor(tu);
        clang_visitChildren(startCursor, parseCode, &result);
        
        clang_disposeTranslationUnit(tu);
    }
    
    std::map<std::string, ScriptingParserResult::System> uniqueSystems;
    
    for(auto& s : result.systems) {
        uniqueSystems[s.name] = s;
    }
    
    result.systems.clear();
    
    for(auto& s : uniqueSystems) {
        result.systems.push_back(s.second);
    }
    
    std::set<std::string> uniqueComponentNames;
    
    for(auto& s : result.systems) {
        for(auto& c : s.components) {
            auto found = c.find("struct ");
            if (found!=std::string::npos) {
                c = c.substr(0, found) + c.substr(found + 7, c.size() - found - 7);
            } else {
                found = c.find("class ");
                if (found!=std::string::npos) {
                    c = c.substr(0, found) + c.substr(found + 6, c.size() - found - 6);
                }
            }
            uniqueComponentNames.insert(c);
        }
    }
    
    ScriptingParserResult::Components systemComponents;
    
    for(auto& componentName : uniqueComponentNames) {
        auto* component = result.FindComponent(componentName);
        if (!component) continue;
        if (!predicate(componentName)) continue;
        systemComponents.push_back(*component);
    }
    
    result.components = systemComponents;
    
    return true;
}

std::string getCursorSpelling2( CXCursor cursor )
{
  CXString cursorSpelling = clang_getCursorSpelling( cursor );
  std::string result      = clang_getCString( cursorSpelling );

  clang_disposeString( cursorSpelling );
  return result;
}

std::string getCursorType( CXCursor cursor )
{
  CXType type = clang_getCursorType( cursor );
  CXString cursorSpelling = clang_getTypeSpelling(type);

  std::string result      = clang_getCString( cursorSpelling );

  clang_disposeString( cursorSpelling );
  return result;
}

static std::string lastDerivedName = "";

CXChildVisitResult parseCode(CXCursor cursor, CXCursor parent, CXClientData clientData) {
    CXSourceLocation location = clang_getCursorLocation( cursor );
    if (clang_Location_isInSystemHeader(location) != 0) {
        return CXChildVisit_Continue;
    }
    
    ScriptingParserResult& result = *static_cast<ScriptingParserResult*>(clientData);
    
    std::string cursorSpelling = getCursorSpelling2(cursor);
    
    static bool isSystem = false;
    static std::string nameSpace = "";
    
    if (parent.kind == CXCursor_TranslationUnit) {
        nameSpace = "";
        isSystem = false;
    }
    
    if (cursor.kind == CXCursor_TemplateRef) {
        lastDerivedName = cursorSpelling;
    }
    
    if (cursor.kind == CXCursor_Namespace) {
        nameSpace = cursorSpelling;
        isSystem = false;
    } else if (cursor.kind == CXCursor_StructDecl || cursor.kind == CXCursor_ClassDecl) {
        
        
        ScriptingParserResult::Component component;
        if (nameSpace!="") {
            component.name = nameSpace +"::" + cursorSpelling;
        } else {
            component.name = cursorSpelling;
        }
        
        result.components.push_back(component);
        
        isSystem = false;
    } else if (cursor.kind == CXCursor_TemplateRef && cursorSpelling == "System") {
        result.systems.push_back({result.components.back().name});
        isSystem = true;
    } else if (cursor.kind == CXCursor_TypeRef && isSystem && parent.kind == CXCursor_CXXBaseSpecifier && lastDerivedName!="SystemDependencies") {
        result.systems.back().components.push_back(cursorSpelling);
    } else if (cursor.kind == CXCursor_FieldDecl && !result.components.empty()) {
        isSystem = false;
    
        //std::cout << scriptData.components.back().name<<":" << cursorSpelling << " : " << getCursorType(cursor) << std::endl;
        result.components.back().fields.push_back({cursorSpelling, getCursorType(cursor)});
    }
    
    return CXChildVisit_Recurse;
}


std::string ScriptingParser::GetFirstFolder(const std::string &path) {
    
    std::string foundPath = "";
    
    DIR *dir = opendir(path.c_str());

    struct dirent *entry = readdir(dir);

    while (entry != NULL)
    {
        if (entry->d_type == DT_DIR) {
            foundPath = std::string(entry->d_name);
            
            if (foundPath != "." && foundPath!="..") {
                break;
            }
        }
        entry = readdir(dir);
    }

    closedir(dir);
    
    return foundPath;
}


std::string ScriptingParser::pipe_to_string( const char* command )
{
   FILE* file = popen( command, "r" ) ;

   if( file )
   {
       std::stringstream stm;

       constexpr std::size_t MAX_LINE_SZ = 1024 ;
       char line[MAX_LINE_SZ] ;

       while( fgets( line, MAX_LINE_SZ, file ) ) stm << line;

       pclose(file) ;
       std::string str = stm.str() ;
       str = str.substr(0,str.length() - 1);
       return str;
   }

   return "" ;
}


std::vector<std::string> ScriptingParser::CreateDefaultArguments() {
    
    std::vector<std::string> arguments;
    
    std::string sdkPath = pipe_to_string("xcrun --sdk macosx --show-sdk-path");
    std::string sdkInclude = sdkPath + "/usr/include";
    std::string clangDir = sdkPath + "/../../usr/";
    
    //arguments.push_back("-v");
    arguments.push_back("-std=c++17");
    arguments.push_back("-fno-rtti");
    arguments.push_back("-Wno-nullability-completeness");
    arguments.push_back("-I" + clangDir + "/include/c++/v1");
    arguments.push_back("-I" + clangDir + "/lib/clang/" + GetFirstFolder(clangDir + "/lib/clang") + "/include");
    arguments.push_back("-I" + sdkInclude);
    
    return arguments;
}

std::vector<std::string> ScriptingParser::GetArguments(const ScriptingContext &context) {
    
    if (defaultArguments.empty()) {
        defaultArguments = CreateDefaultArguments();
    }
    
    std::vector<std::string> arguments = defaultArguments;
    
    for(auto includePath : context.GetIncludePaths()) {
        arguments.push_back("-I" + includePath);
    }
    
    return arguments;
}
