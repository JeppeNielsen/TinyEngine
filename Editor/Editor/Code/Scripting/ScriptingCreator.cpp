//
//  ScriptingCreator.cpp
//  ScriptingTesting
//
//  Created by Jeppe Nielsen on 20/10/2021.
//

#include "ScriptingCreator.hpp"


using namespace Tiny;

ScriptingCreator::ScriptingCreator() { 
    
}

void ScriptingCreator::WriteMainCppFile(std::ostream& stream, ScriptingParserResult& result) {
    WriteIncludes(stream, result);
    stream << "\n";
    WriteECSDefinitions(stream, result);
    stream << "\n";
    WriteRegistryFunctions(stream, result);
    stream << "\n";
    WriteSceneFunctions(stream, result);
    stream << "\n";
    WriteTypeInfoFactory(stream, result);
    stream << "\n";
}

void ScriptingCreator::WriteIncludes(std::ostream &stream, ScriptingParserResult &result) {
    stream << "#include \"Scene.hpp\"\n";
    stream << "#include <vector>\n";
    stream << "using namespace Tiny;\n";
}

void ScriptingCreator::WriteECSDefinitions(std::ostream &stream, ScriptingParserResult &result) {
    WriteComponents(stream, result);
    WriteSystems(stream, result);
    stream << "using RegistryType = Registry<Components>;\n";
    stream << "using SceneType = Scene<RegistryType, Systems>;\n";
}

void ScriptingCreator::WriteComponents(std::ostream &stream, ScriptingParserResult &result) {
    stream << "using Components = ComponentTypes<";
    for (int i=0; i<result.components.size(); ++i) {
        stream << result.components[i].name;
        if (i<result.components.size() - 1) {
            stream << ", ";
        }
    }
    stream << ">;\n";
    
}

void ScriptingCreator::WriteSystems(std::ostream &stream, ScriptingParserResult &result) {
    stream << "using Systems = SystemTypes<";
    for (int i=0; i<result.systems.size(); ++i) {
        stream << result.systems[i].name;
        if (i<result.systems.size() - 1) {
            stream << ", ";
        }
    }
    stream << ">;\n";
}


void ScriptingCreator::WriteRegistryFunctions(std::ostream &stream, Tiny::ScriptingParserResult &result) {
    stream << "extern \"C\" { \n" ;
        stream << "void* CreateRegistry() {\n";
        stream << "RegistryType* registry = new RegistryType();\n";
        stream << "return registry;\n";
        stream << "}\n";
    stream << "}\n";
    
    stream << "\n";

    stream << "extern \"C\" { \n" ;
        stream << "void DeleteRegistry(void* registryPtr) {\n";
        stream << "RegistryType* registry = reinterpret_cast<RegistryType*>(registryPtr);\n";
        stream << "delete registry;\n";
        stream << "}\n";
    stream << "}\n";
}

void ScriptingCreator::WriteSceneFunctions(std::ostream &stream, Tiny::ScriptingParserResult &result) {
    stream << "extern \"C\" { \n" ;
        stream << "IScene* CreateScene(void* registryPtr) {\n";
        stream << "RegistryType* registry = reinterpret_cast<RegistryType*>(registryPtr);\n";
        stream << "SceneType* scene = new SceneType(*registry);\n";
        stream << "return scene;\n";
        stream << "}\n";
    stream << "}\n";
    
    stream << "\n";
    
    stream << "extern \"C\" { \n" ;
        stream << "void DeleteScene(IScene* scenePtr) {\n";
        stream << "SceneType* scene = reinterpret_cast<SceneType*>(scenePtr);\n";
        stream << "delete scene;\n";
        stream << "}\n";
    stream << "}\n";
    
    stream << "\n";
    
    stream << "extern \"C\" { \n" ;
        stream << "void AddComponent(IScene* scenePtr, GameObject gameObject, int componentId) {\n";
            stream << "SceneType* scene = reinterpret_cast<SceneType*>(scenePtr);\n";
            stream << "static std::vector<std::function<void(SceneType*, GameObject)>> createComponents = {\n";
                for(auto& component : result.components) {
                    stream<<"[](SceneType* s, GameObject g) {\n";
                    stream<<"s->AddComponent<"<< component.name<<">(g);\n";
                    stream<<"},\n";
                }
            stream << "};\n";
            stream << "createComponents[componentId](scene, gameObject);\n";
        stream << "}\n";
        
    stream << "}\n";
    stream << "\n";
    
    stream << "extern \"C\" { \n" ;
        stream << "TypeInfo* GetComponent(IScene* scenePtr, GameObject gameObject, int componentId) {\n";
        
            stream << "SceneType* scene = reinterpret_cast<SceneType*>(scenePtr);\n";
            stream << "static std::vector<std::function<TypeInfo*(SceneType*, GameObject)>> getComponents = {\n";
                for(auto& component : result.components) {
                    stream<<"[](SceneType* s, GameObject g) {\n";
                        stream<<"auto& c = s->GetComponent<"<< component.name<<">(g);\n";
                        stream<<"TypeInfo* info = new TypeInfo(\""<<component.name << "\");\n";
                        for(auto& field : component.fields) {
                            stream<<"info->AddField(\""<< field.name <<"\",c."<< field.name <<");\n";
                        }
                        stream<<"return info;";
                    stream<<"},\n";
                }
            stream << "};\n";
            stream << "return getComponents[componentId](scene, gameObject);\n";
            
        stream << "}\n";
    stream << "}\n";
    stream << "\n";
}

void ScriptingCreator::WriteTypeInfoFactory(std::ostream& stream, ScriptingParserResult& result) {
   /*
    
    TypeInfo GetComponentTypeInfo(int componentTypeId, SceneType* scene, GameObject gameObject) {
        static std::unordered_map<int, std::function<TypeInfo(SceneType*, GameObject)>> getTypeInfo = {
            {0, [](SceneType* s, GameObject g) -> TypeInfo {
                auto& component = s->GetComponent<Colorizer>(g);
                TypeInfo typeInfo("Colorizer");
                typeInfo.AddField("hue", component.hue);
                typeInfo.AddField("speed", component.speed);
                return typeInfo;
            }},
        };
       
        return getTypeInfo[componentTypeId](scene, gameObject);
    }

    
    */
}
