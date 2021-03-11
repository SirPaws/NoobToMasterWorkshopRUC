
var LibrarypWindow  = {
    $pWindow__deps: ['$Browser'],
    $pWindow: {
        windows:       [],
        keys:          [],
        mouse_buttons: [],
        active: null,
        current_fptr: null, 
        pWindowFlags: {
            PSTD_NO_WINDOW_FLAGS: 0,
            PSTD_FULL_SCREEN: 0,
            PSTD_NO_WINDOW_FLAGS: 0,
        },
        pState: {
            PSTD_PRESSED:  1,
            PSTD_HELD:     2,
            PSTD_RELEASED: 0,
        },
        pKey: {
            PSTD_SPACE:         32,
            PSTD_KEY_0:         48,
            PSTD_KEY_1:         49,
            PSTD_KEY_2:         50,
            PSTD_KEY_3:         51,
            PSTD_KEY_4:         52,
            PSTD_KEY_5:         53,
            PSTD_KEY_6:         54,
            PSTD_KEY_7:         55,
            PSTD_KEY_8:         56,
            PSTD_KEY_9:         57,
            PSTD_KEY_A:         97,
            PSTD_KEY_B:         98,
            PSTD_KEY_C:         99,
            PSTD_KEY_D:         100,
            PSTD_KEY_E:         101,
            PSTD_KEY_F:         102,
            PSTD_KEY_G:         103,
            PSTD_KEY_H:         104,
            PSTD_KEY_I:         105,
            PSTD_KEY_J:         106,
            PSTD_KEY_K:         107,
            PSTD_KEY_L:         108,
            PSTD_KEY_M:         109,
            PSTD_KEY_N:         110,
            PSTD_KEY_O:         111,
            PSTD_KEY_P:         112,
            PSTD_KEY_Q:         113,
            PSTD_KEY_R:         114,
            PSTD_KEY_S:         115,
            PSTD_KEY_T:         116,
            PSTD_KEY_U:         117,
            PSTD_KEY_V:         118,
            PSTD_KEY_W:         119,
            PSTD_KEY_X:         120,
            PSTD_KEY_Y:         121,
            PSTD_KEY_Z:         122,
            
            PSTD_ENTER:         256,
            PSTD_TAB:           258,
            PSTD_DELETE:        259,
            PSTD_END:           260,
            PSTD_HOME:          261,
            PSTD_INSERT:        262,
            PSTD_PAGE_DOWN:     263,
            PSTD_PAGE_UP:       264,
            PSTD_ARROW_DOWN:    265,
            PSTD_ARROW_LEFT:    266,
            PSTD_ARROW_RIGHT:   267,
            PSTD_ARROW_UP:      268,
            PSTD_ESCAPE:        269,
            PSTD_CAPSLOCK:      270,
            
            PSTD_LEFT_ALT:      273,
            PSTD_RIGHT_ALT:     274,
            PSTD_ALT:           275,

            PSTD_LEFT_CONTROL:  289,
            PSTD_RIGHT_CONTROL: 290,
            PSTD_CONTROL:       291,

            PSTD_LEFT_SUPER:    321,
            PSTD_RIGHT_SUPER:   322,
            PSTD_SUPER:         323,

            PSTD_LEFT_SHIFT:    385,
            PSTD_RIGHT_SHIFT:   386,
            PSTD_SHIFT:         387,
        },
        pMods: {
            PSTD_MOD_SHIFT:   (1 << 0),
            PSTD_MOD_CONTROL: (1 << 1),
            PSTD_MOD_ALT:     (1 << 2),
            PSTD_MOD_SUPER:   (1 << 3),
        },
        pDomKeyCodeToKey: function (key_code, is_left) {
            switch(key_code) {
            case 0x31: return pWindow.pKey.PSTD_KEY_1;
            case 0x32: return pWindow.pKey.PSTD_KEY_2;
            case 0x33: return pWindow.pKey.PSTD_KEY_3;
            case 0x34: return pWindow.pKey.PSTD_KEY_4;
            case 0x35: return pWindow.pKey.PSTD_KEY_5;
            case 0x36: return pWindow.pKey.PSTD_KEY_6;
            case 0x37: return pWindow.pKey.PSTD_KEY_7;
            case 0x38: return pWindow.pKey.PSTD_KEY_8;
            case 0x39: return pWindow.pKey.PSTD_KEY_9;
            case 0x30: return pWindow.pKey.PSTD_KEY_0;
            case 0x41: return pWindow.pKey.PSTD_KEY_A;
            case 0x42: return pWindow.pKey.PSTD_KEY_B;
            case 0x43: return pWindow.pKey.PSTD_KEY_C;
            case 0x44: return pWindow.pKey.PSTD_KEY_D;
            case 0x45: return pWindow.pKey.PSTD_KEY_E;
            case 0x46: return pWindow.pKey.PSTD_KEY_F;
            case 0x47: return pWindow.pKey.PSTD_KEY_G;
            case 0x48: return pWindow.pKey.PSTD_KEY_H;
            case 0x49: return pWindow.pKey.PSTD_KEY_I;
            case 0x4A: return pWindow.pKey.PSTD_KEY_J;
            case 0x4B: return pWindow.pKey.PSTD_KEY_K;
            case 0x4C: return pWindow.pKey.PSTD_KEY_L;
            case 0x4D: return pWindow.pKey.PSTD_KEY_M;
            case 0x4E: return pWindow.pKey.PSTD_KEY_N;
            case 0x4F: return pWindow.pKey.PSTD_KEY_O;
            case 0x50: return pWindow.pKey.PSTD_KEY_P;
            case 0x51: return pWindow.pKey.PSTD_KEY_Q;
            case 0x52: return pWindow.pKey.PSTD_KEY_R;
            case 0x53: return pWindow.pKey.PSTD_KEY_S;
            case 0x54: return pWindow.pKey.PSTD_KEY_T;
            case 0x55: return pWindow.pKey.PSTD_KEY_U;
            case 0x56: return pWindow.pKey.PSTD_KEY_V;
            case 0x57: return pWindow.pKey.PSTD_KEY_W;
            case 0x58: return pWindow.pKey.PSTD_KEY_X;
            case 0x59: return pWindow.pKey.PSTD_KEY_Y;
            case 0x5A: return pWindow.pKey.PSTD_KEY_Z;
            
            case 0x12: return (is_left ? 
                     pWindow.pKey.PSTD_LEFT_ALT     : pWindow.pKey.PSTD_RIGHT_ALT);
            case 0x11: return (is_left ? 
                     pWindow.pKey.PSTD_LEFT_CONTROL : pWindow.pKey.PSTD_RIGHT_CONTROL);
            case 0x10: return (is_left ? 
                     pWindow.pKey.PSTD_LEFT_SHIFT   : pWindow.pKey.PSTD_RIGHT_SHIFT);
        
            case 0x5B: return pWindow.pKey.PSTD_LEFT_SUPER
            case 0x5C: return pWindow.pKey.PSTD_RIGHT_SUPER
        
            case 0x14: return pWindow.pKey.PSTD_CAPSLOCK;
            case 0x0D: return pWindow.pKey.PSTD_ENTER;
            case 0x20: return pWindow.pKey.PSTD_SPACE;
            case 0x09: return pWindow.pKey.PSTD_TAB;
            case 0x2E: return pWindow.pKey.PSTD_DELETE;
            case 0x23: return pWindow.pKey.PSTD_END;
            case 0x24: return pWindow.pKey.PSTD_HOME;
            case 0x2D: return pWindow.pKey.PSTD_INSERT;
            case 0x22: return pWindow.pKey.PSTD_PAGE_DOWN;
            case 0x21: return pWindow.pKey.PSTD_PAGE_UP;
            case 0x28: return pWindow.pKey.PSTD_ARROW_DOWN;
            case 0x25: return pWindow.pKey.PSTD_ARROW_LEFT;
            case 0x27: return pWindow.pKey.PSTD_ARROW_RIGHT;
            case 0x26: return pWindow.pKey.PSTD_ARROW_UP;
            case 0x1B: return pWindow.pKey.PSTD_ESCAPE;
            default: return key_code + is_left;
            }
        },
        pKeyToIndex: function(key) {
            switch(key) {
            case pWindow.pKey.PSTD_SPACE:            return  0;
            case pWindow.pKey.PSTD_KEY_0:            return  1;
            case pWindow.pKey.PSTD_KEY_1:            return  2;
            case pWindow.pKey.PSTD_KEY_2:            return  3;
            case pWindow.pKey.PSTD_KEY_3:            return  4;
            case pWindow.pKey.PSTD_KEY_4:            return  5;
            case pWindow.pKey.PSTD_KEY_5:            return  6;
            case pWindow.pKey.PSTD_KEY_6:            return  7;
            case pWindow.pKey.PSTD_KEY_7:            return  8;
            case pWindow.pKey.PSTD_KEY_8:            return  9;
            case pWindow.pKey.PSTD_KEY_9:            return 10;
            case pWindow.pKey.PSTD_KEY_A:            return 11;
            case pWindow.pKey.PSTD_KEY_B:            return 12;
            case pWindow.pKey.PSTD_KEY_C:            return 13;
            case pWindow.pKey.PSTD_KEY_D:            return 14;
            case pWindow.pKey.PSTD_KEY_E:            return 15;
            case pWindow.pKey.PSTD_KEY_F:            return 16;
            case pWindow.pKey.PSTD_KEY_G:            return 17;
            case pWindow.pKey.PSTD_KEY_H:            return 18;
            case pWindow.pKey.PSTD_KEY_I:            return 19;
            case pWindow.pKey.PSTD_KEY_J:            return 21;
            case pWindow.pKey.PSTD_KEY_K:            return 22;
            case pWindow.pKey.PSTD_KEY_L:            return 23;
            case pWindow.pKey.PSTD_KEY_M:            return 24;
            case pWindow.pKey.PSTD_KEY_N:            return 25;
            case pWindow.pKey.PSTD_KEY_O:            return 26;
            case pWindow.pKey.PSTD_KEY_P:            return 27;
            case pWindow.pKey.PSTD_KEY_Q:            return 28;
            case pWindow.pKey.PSTD_KEY_R:            return 29;
            case pWindow.pKey.PSTD_KEY_S:            return 30;
            case pWindow.pKey.PSTD_KEY_T:            return 31;
            case pWindow.pKey.PSTD_KEY_U:            return 32;
            case pWindow.pKey.PSTD_KEY_V:            return 33;
            case pWindow.pKey.PSTD_KEY_W:            return 34;
            case pWindow.pKey.PSTD_KEY_X:            return 35;
            case pWindow.pKey.PSTD_KEY_Y:            return 36;
            case pWindow.pKey.PSTD_KEY_Z:            return 37;
            
            case pWindow.pKey.PSTD_ENTER:            return 38;
            case pWindow.pKey.PSTD_TAB:              return 39;
            case pWindow.pKey.PSTD_DELETE:           return 40;
            case pWindow.pKey.PSTD_END:              return 41;
            case pWindow.pKey.PSTD_HOME:             return 42;
            case pWindow.pKey.PSTD_INSERT:           return 43;
            case pWindow.pKey.PSTD_PAGE_DOWN:        return 44;
            case pWindow.pKey.PSTD_PAGE_UP:          return 45;
            case pWindow.pKey.PSTD_ARROW_DOWN:       return 46;
            case pWindow.pKey.PSTD_ARROW_LEFT:       return 47;
            case pWindow.pKey.PSTD_ARROW_RIGHT:      return 48;
            case pWindow.pKey.PSTD_ARROW_UP:         return 49;
            case pWindow.pKey.PSTD_ESCAPE:           return 50;
            case pWindow.pKey.PSTD_CAPSLOCK:         return 51;
            
            case pWindow.pKey.PSTD_LEFT_ALT:         return 52;
            case pWindow.pKey.PSTD_RIGHT_ALT:        return 53;
           
            case pWindow.pKey.PSTD_LEFT_CONTROL:     return 54;
            case pWindow.pKey.PSTD_RIGHT_CONTROL:    return 55;
          
            case pWindow.pKey.PSTD_LEFT_SUPER:       return 56;
            case pWindow.pKey.PSTD_RIGHT_SUPER:      return 57;
         
            case pWindow.pKey.PSTD_LEFT_SHIFT:       return 58;
            case pWindow.pKey.PSTD_RIGHT_SHIFT:      return 59;
            default: return key;
            }
        },

        pWindowInfo: function(info) {
            this.x      = getValue(info + 4 * 0, 'i32');
            this.y      = getValue(info + 4 * 1, 'i32');
            this.width  = getValue(info + 4 * 2, 'i32');
            this.height = getValue(info + 4 * 3, 'i32');
            let c_str = getValue(info + 4*4, 'i8*');
            
            if (c_str === 0) 
                 this.title = ""
            else this.title  = AsciiToString(c_str);
            
            if (this.x <= 0)      this.x = 'default';
            if (this.y <= 0)      this.y = 'default';
            if (this.width  <= 0) this.width  = 960;
            if (this.height <= 0) this.height = 540;

            return this;
        },
        pWindow: function(context, canvas, x, y, width, height, title) {
            canvas.width   = width;
            canvas.height  = height;
            document.title = title;

            this.id     = 0;
            this.x      = x;
            this.y      = y;
            this.width  = width;
            this.height = height;
            this.title  = title;
            this.event_handler = {
                key_event_handler:      [],
                mouse_button_handler:   [],
                mouse_scroll_handler:   [],
                mouse_position_handler: [],
            }
            this.context   = context;
            this.canvas    = canvas;
            return this;
        },
        isKeyDown: function(key) {
            let pKey = pWindow.pKey;
            let keys = pWindow.keys;
            let getIndex = pWindow.pKeyToIndex;
            if (!keys) return 0;

            if (key == pKey.PSTD_SHIFT) {
                if (keys[getIndex(pKey.PSTD_LEFT_SHIFT)]) 
                    return keys[getIndex(pKey.PSTD_LEFT_SHIFT)];
                else { 
                    return keys[getIndex(pKey.PSTD_RIGHT_SHIFT)] ?? 0;
                }
            }
            else if (key == pKey.PSTD_CONTROL) {
                if (keys[getIndex(pKey.PSTD_LEFT_CONTROL)]) 
                    return keys[getIndex(pKey.PSTD_LEFT_CONTROL)];
                else { 
                    return keys[getIndex(pKey.PSTD_RIGHT_CONTROL)] ?? 0;
                }
            }
            else if (key == pKey.PSTD_ALT) {
                if (keys[getIndex(pKey.PSTD_LEFT_ALT)]) 
                    return keys[getIndex(pKey.PSTD_LEFT_ALT)];
                else { 
                    return keys[getIndex(pKey.PSTD_RIGHT_ALT)] ?? 0;
                }
            }
            else if (key == pKey.PSTD_SUPER) {
                if (keys[getIndex(pKey.PSTD_LEFT_SUPER)]) 
                    return keys[getIndex(pKey.PSTD_LEFT_SUPER)];
                else { 
                    return keys[getIndex(pKey.PSTD_RIGHT_SUPER)] ?? 0;
                }
            }
            return keys[getIndex(key)] ?? 0;
        },
        getMods:  function() {
            let keyDown = pWindow.isKeyDown; 
            let pKey    = pWindow.pKey;
            let pMods   = pWindow.pMods;
            let mods = 0;
            if (keyDown(pKey.PSTD_SHIFT))   mods = pMods.PSTD_MOD_SHIFT;
            if (keyDown(pKey.PSTD_CONTROL)) mods = mods | pMods.PSTD_MOD_CONTROL;
            if (keyDown(pKey.PSTD_ALT))     mods = mods | pMods.PSTD_MOD_ALT;
            if (keyDown(pKey.PSTD_SUPER))   mods = mods | pMods.PSTD_MOD_SUPER;
            return mods;
        },
        getWindow: function(id) {
            if (id == 0) abort('invalid window');
            return this.windows[id - 1];
        },
        onKeyChanged: function(event, new_state) {

            let is_left  = event.location == KeyboardEvent.DOM_KEY_LOCATION_LEFT;
            let key   = pWindow.pDomKeyCodeToKey(event.keyCode, is_left);
            let index = pWindow.pKeyToIndex(key);

            if (new_state && this.keys[index])
                 this.keys[index] = pWindow.pState.PSTD_HELD
            else this.keys[index] = new_state;

            let mods = pWindow.getMods();

            if (!this.active) return;
            let window   = pWindow.getWindow(this.active);
            let handlers = window.event_handler.key_event_handler;
            for (let i = handlers.length - 1; i > -1; i--) {
                let handler = handlers[i];
                current_fptr = handler;
                let callback = {{{ makeDynCall('Ciiii', 'handler') }}};
                let result = callback(this.active, this.keys[index], key, mods);
                if (result) break;
            }
        },
        onKeyDown: function(event) {
            pWindow.onKeyChanged(event, pWindow.pState.PSTD_PRESSED);
        },
        onKeyUp: function(event) {
            pWindow.onKeyChanged(event, pWindow.pState.PSTD_RELEASED);
        },
        onMouseChanged: function(event, new_state) {

            if (event.target != Module['canvas']) return;

            let button = event.button;
            if (button == 1) { // middle mouse and right mouse is flipped
                button = 2;
            }
            else if(button == 2) {
                button = 1;
            }

            if (new_state && this.mouse_buttons[button])
                 this.mouse_buttons[button] = pWindow.pState.PSTD_HELD
            else this.mouse_buttons[button] = new_state;

            let mods = pWindow.getMods();

            if (!this.active) return;
            let window   = pWindow.getWindow(this.active);
            let handlers = window.event_handler.mouse_button_handler;
            for (let i = handlers.length - 1; i > -1; i--) {
                let handler = handlers[i];
                current_fptr = handler;
                let callback = {{{ makeDynCall('Ciiii', 'handler') }}};
                let result = callback(this.active, this.mouse_buttons[button], button, mods);
                if (result) break;
            }
        },
        onMouseDown: function(event) {
            pWindow.onMouseChanged(event, pWindow.pState.PSTD_PRESSED);
        },
        onMouseUp: function(event) {
            pWindow.onMouseChanged(event, pWindow.pState.PSTD_RELEASED);
        },
        onMouseMove: function(event) {
            if (!pWindow.active) return;

            Browser.calculateMouseEvent(event);

            let window   = pWindow.getWindow(pWindow.active);
            let handlers = window.event_handler.mouse_position_handler;
            for (let i = handlers.length - 1; i > -1; i--) {
                let handler = handlers[i];
                current_fptr = handler;
                let callback = {{{ makeDynCall('Cidd', 'handler') }}};
                let result = callback(this.active, Browser.mouseX, Browser.mouseY);
                if (result) break;
            }
        }
    },
    pCreateWindow: function(info) {
        let window_info = new pWindow.pWindowInfo(info);

        let ctx = Browser.createContext(Module['canvas'], false, true);
        if (!ctx) return 0;

        let new_canvas = document.createElement('canvas');
        new_canvas.width = window_info.width;
        new_canvas.height = window_info.height;
        new_canvas.id = 'canvas';

        let p_window = new pWindow.pWindow(ctx, Module['canvas'],
            window_info.x, window_info.y, window_info.width, window_info.height, window_info.title);

        pWindow.windows.push(p_window);
        let id = pWindow.windows.length; 
        p_window.id = id;

        let ui = document.getElementById('controls');
        ui.style.display = 'none';
        let cmd = document.getElementById('output');
        cmd.style.display = 'none';

        let style = Module['canvas'].style;
        style.display = 'block';
        if (p_window.x == 'default') {
            style.marginLeft  = 'auto';
            style.marginRight = 'auto';
        } else {
            style.position = 'relative';
            style.left     = p_window.x + 'px'
        }
        if (p_window.y == 'default') {
            style.marginTop    = 'auto';
            style.marginBottom = 'auto';
        } else {
            style.position = 'relative';
            style.top     = p_window.y + 'px'
        }

        window.addEventListener("keydown",  pWindow.onKeyDown);
        window.addEventListener("keyup",    pWindow.onKeyUp);
        Module['canvas'].addEventListener("mousedown",  pWindow.onMouseDown);
        Module['canvas'].addEventListener("mouseup",    pWindow.onMouseUp);
        Module['canvas'].addEventListener("mousemove",  pWindow.onMouseMove);

        return id;
    }, 
    pDebugUpdate: function() {
        let command_line_output = document.getElementById('output');
        if (command_line_output && command_line_output.textLength > 10000) {
            command_line_output.value = "";
        }
    },
    pSetActiveWindow: function(window) {
        let old = pWindow.active;
        pWindow.active = window;
        return old ?? 0;
    },
    pGetMonitorDimensions: function(dim) {
        setValue(dim + 4 * 0, window.width,  'i32');
        setValue(dim + 4 * 1, window.height, 'i32');
        window.width;
    },
    pPushKeyboardEventHandler: function(window_id, event_handler) {
        let window = pWindow.getWindow(window_id);
        window.event_handler['key_event_handler'].push(event_handler);
    },
    pPushMouseButtonEventHandler: function(window_id, event_handler) {
        let window = pWindow.getWindow(window_id);
        window.event_handler['mouse_button_handler'].push(event_handler);
    },
    pPushMousePositionEventHandler: function(window_id, event_handler) {
        let window = pWindow.getWindow(window_id);
        window.event_handler['mouse_position_handler'].push(event_handler);
    },
    pPushMouseScrollEventHandler: function(window_id, event_handler) {
        let window = pWindow.getWindow(window_id);
        window.event_handler['mouse_scroll_handler'].push(event_handler);

    },
}
autoAddDeps(LibrarypWindow, '$pWindow')
mergeInto(LibraryManager.library, LibrarypWindow);

