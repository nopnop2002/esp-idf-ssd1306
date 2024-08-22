typedef enum {
    APP_EVENT_KEYBOARD = 0,
    APP_EVENT_MOUSE
} hid_event_type_t;

typedef struct {
    enum key_state {
        KEY_STATE_PRESSED = 0x00,
        KEY_STATE_RELEASED = 0x01
    } state;
    uint8_t modifier;
    uint8_t key_code;
	unsigned char key_char;
} key_event_t;

typedef struct {
	int x_displacement;
	int y_displacement;
	int button1;
	int button2;
	int button3;
} mouse_event_t;

typedef struct {
	hid_event_type_t hid_event_type;
	key_event_t key_event;
	mouse_event_t mouse_event;
} HID_EVENT_t;
