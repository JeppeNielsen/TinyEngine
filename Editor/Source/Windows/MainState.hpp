//
//  MainWindow.hpp
//  TinyEditor
//
//  Created by Jeppe Nielsen on 05/12/2021.
//

#include "IState.hpp"
#include "Context/EditorContext.hpp"

namespace TinyEditor {

class MainState : public Tiny::IState {
public:
    void Initialize();
    void Update(float dt);
    void Render();
private:
    EditorContext context;
};

}
