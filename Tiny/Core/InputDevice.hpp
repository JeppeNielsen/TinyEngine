#pragma once
#include <vector>
#include "InputManager.hpp"
#include <map>
#include <string>
#include "Property.hpp"
#include "Math.hpp"

namespace Tiny {
    class InputDevice  {
	public:
		InputDevice();
		~InputDevice();

		void Initialize(int maxTouches);

		struct Touch {
			Touch() : IsDown(false), Position(0), swallowedDepth(-1) {}
			bool IsDown;
			ivec2 Position;
            int swallowedDepth;
        };

		void SetTouchPosition(int index, const ivec2& position);
		void SetTouch(int index, bool isDown, const ivec2& position);
		const ivec2& GetTouchPosition(int index);

		void StartFrame();
        void EndFrame();

		void SetButton(const std::string& button, bool isDown, ModifierKey modifierKey);
		void ReleaseAllButtons();
        
        bool KeyboardActive;
        std::string KeyboardText;
        
        void SetKeyboard(std::string text, bool active);
        
        struct KeyboardEventData {
            std::string text;
            bool active;
        };
        
        Event<KeyboardEventData> KeyboardChanged;
        
        void UpdateInputManager(InputManager& inputManager);
        
        void SetScroll(float delta);
        
        void SwallowTouch(int index, int depth);
        bool IsTouchSwallowed(int index, int depth);
        
	public:

		typedef std::vector<Touch> Touches;

		Touches currentTouches;
		Touches previousTouches;

		typedef std::map<std::string, ModifierKey> Buttons;

		Buttons currentButtons;
		Buttons previousButtons;

		int maxTouches;
        
        ivec2 zero;
        
        bool updating;
        
        typedef std::vector<float> ScrollValues;
        ScrollValues scrollValues;
	};
}

