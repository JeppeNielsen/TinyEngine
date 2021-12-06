//
//  MainWindow.hpp
//  TinyEditor
//
//  Created by Jeppe Nielsen on 05/12/2021.
//

#include "IState.hpp"

namespace TinyEditor {

class MainWindow : public Tiny::IState {
public:
    void Initialize();
    void Update(float dt);
    void Render();
};

}
