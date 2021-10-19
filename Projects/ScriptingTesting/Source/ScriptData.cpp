//
//  ScriptData.cpp
//  PocketEditor
//
//  Created by Jeppe Nielsen on 15/05/2017.
//  Copyright © 2017 Jeppe Nielsen. All rights reserved.
//

#include "ScriptData.hpp"
#include <clang-c/Index.h>
#include <iostream>
#include <set>
#include <map>
#include <dirent.h>
#include <sstream>

using namespace Tiny;

ScriptData::ScriptData(const std::string& clangPath) : clangLocation(clangPath) {
    
}

void ScriptData::Clear() {
    components.clear();
    systems.clear();
}

CXChildVisitResult parseCode(CXCursor cursor, CXCursor parent, CXClientData clientData);



bool ScriptData::Parse(const ScriptingContext& context, const std::function<bool(const std::string&)>& predicate) {
    
    
    std::vector<std::string> contextArguments = GetArguments(context);
    
    std::vector<const char*> arguments;
    
    for(auto& contextArgument : contextArguments) {
        arguments.push_back(contextArgument.c_str());
    }
    
    for(auto cppFile : context.cppFiles) {
        CXIndex index = clang_createIndex(0,1);

        // create Translation Unit
        CXTranslationUnit tu = clang_parseTranslationUnit(index, cppFile.c_str(), &arguments[0], (int)arguments.size(), NULL, 0,
                                            CXTranslationUnit_KeepGoing | CXTranslationUnit_IgnoreNonErrorsFromIncludedFiles | CXTranslationUnit_Incomplete);
        
        if (tu == NULL) {
            printf("Cannot parse translation unit\n");
            return false;
        }

        CXCursor startCursor = clang_getTranslationUnitCursor(tu);
        clang_visitChildren(startCursor, parseCode, this);
        
        clang_disposeTranslationUnit(tu);
    }
    
    std::map<std::string, System> uniqueSystems;
    
    for(auto& s : systems) {
        uniqueSystems[s.name] = s;
    }
    
    systems.clear();
    
    for(auto& s : uniqueSystems) {
        systems.push_back(s.second);
    }
    
    std::set<std::string> uniqueComponentNames;
    
    for(auto& s : systems) {
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
    
    Components systemComponents;
    
    for(auto& componentName : uniqueComponentNames) {
        Component* component = FindComponent(componentName);
        if (!component) continue;
        if (!predicate(componentName)) continue;
        systemComponents.push_back(*component);
    }
    
    components = systemComponents;
    
    return true;
}

ScriptData::Component* ScriptData::FindComponent(const std::string &name) {
    for(auto& c : components) {
        if (c.name == name) return &c;
    }
    return nullptr;
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

CXChildVisitResult parseCode(CXCursor cursor, CXCursor parent, CXClientData clientData) {
    CXSourceLocation location = clang_getCursorLocation( cursor );
    if (clang_Location_isInSystemHeader(location) != 0) {
        return CXChildVisit_Continue;
    }
    
    ScriptData& scriptData = *static_cast<ScriptData*>(clientData);
    
    std::string cursorSpelling = getCursorSpelling2(cursor);
    
    static bool isSystem = false;
    static std::string nameSpace = "";
    
    if (parent.kind == CXCursor_TranslationUnit) {
        nameSpace = "";
        isSystem = false;
    }
    
    if (cursor.kind == CXCursor_Namespace) {
        nameSpace = cursorSpelling;
        isSystem = false;
    } else if (cursor.kind == CXCursor_StructDecl || cursor.kind == CXCursor_ClassDecl) {
        
        ScriptData::Component component;
        if (nameSpace!="") {
            component.name = nameSpace +"::" + cursorSpelling;
        } else {
            component.name = cursorSpelling;
        }
        
        scriptData.components.push_back(component);
        
        isSystem = false;
    } else if (cursor.kind == CXCursor_TemplateRef && cursorSpelling == "System") {
        scriptData.systems.push_back({scriptData.components.back().name});
        isSystem = true;
    } else if (cursor.kind == CXCursor_TypeRef && isSystem && parent.kind == CXCursor_CXXBaseSpecifier) {
        scriptData.systems.back().components.push_back(cursorSpelling);
    } else if (cursor.kind == CXCursor_FieldDecl && !scriptData.components.empty()) {
        isSystem = false;
    
        //std::cout << scriptData.components.back().name<<":" << cursorSpelling << " : " << getCursorType(cursor) << std::endl;
        scriptData.components.back().fields.push_back({cursorSpelling, getCursorType(cursor)});
    }
    
    return CXChildVisit_Recurse;
}


std::string ScriptData::GetFirstFolder(const std::string &path) {
    
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


std::string ScriptData::pipe_to_string( const char* command )
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


std::vector<std::string> ScriptData::CreateDefaultArguments() {
    
    std::vector<std::string> arguments;
    
    std::string sdkPath = pipe_to_string("xcrun --sdk macosx --show-sdk-path") + "/usr/include";
    
    arguments.push_back("-v");
    arguments.push_back("-std=c++17");
    arguments.push_back("-stdlib=libc++");
    arguments.push_back("-fno-rtti");
    arguments.push_back("-Wno-nullability-completeness");
    arguments.push_back("-I" + clangLocation + "/include/c++/v1");
    arguments.push_back("-I" + clangLocation + "/lib/clang/" + GetFirstFolder(clangLocation + "/lib/clang") + "/include");
    arguments.push_back("-I" + sdkPath);
    
    /*arguments.push_back("-std=c++11");
    arguments.push_back("-stdlib=libc++");
    arguments.push_back("-I/Users/Jeppe/Downloads/clang+llvm-3.7.0-x86_64-apple-darwin/include/c++/v1");
    arguments.push_back("-I/usr/include");
    arguments.push_back("-I/usr/include/c++/4.2.1/");
    arguments.push_back("-I/Users/Jeppe/Downloads/clang+llvm-3.7.0-x86_64-apple-darwin/lib/clang/3.7.0/include");*/
    
    return arguments;
}

std::vector<std::string> ScriptData::GetArguments(const ScriptingContext &context) {
    
    if (defaultArguments.empty()) {
        defaultArguments = CreateDefaultArguments();
    }
    
    std::vector<std::string> arguments = defaultArguments;
    
    for(auto includePath : context.GetIncludePaths()) {
        arguments.push_back("-I" + includePath);
    }
    
    return arguments;
}
