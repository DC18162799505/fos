#ifndef      _KEYBOARD_H_
#define      _KEYBOARD_H_

#define Key_empty          0

#define EXT	    0x0100		/* Normal function keys		*/
#define CTRL	0x0200		/* Control key			*/
#define SHIFT	0x0400		/* Shift key			*/
#define ALT	    0x0800		/* Alternate key		*/
#define EXTKEY	0x1000		/* extended keycode		*/
#define HASCAPS	0x2000		/* Caps Lock has effect		*/
#define BREAKFL 0x4000      /* break flages*/

/* Numeric keypad */
#define HOME	(0x01 + EXT)
#define END	    (0x02 + EXT)
#define UP	    (0x03 + EXT)
#define DOWN	(0x04 + EXT)
#define LEFT	(0x05 + EXT)
#define RIGHT	(0x06 + EXT)
#define PGUP	(0x07 + EXT)
#define PGDN	(0x08 + EXT)
#define DEL     (0x09 + EXT)  /* delete   */
#define INSERT	(0x0A + EXT)  /* insert   */
#define PRINTSCREEN	(0x0B + EXT)	/* Print Screen	*/
#define PAUSEBREAK	(0x0C + EXT)	/* Pause/Break	*/

/* Function keys */
#define F1	(0x10 + EXT)
#define F2	(0x11 + EXT)
#define F3	(0x12 + EXT)
#define F4	(0x13 + EXT)
#define F5	(0x14 + EXT)
#define F6	(0x15 + EXT)
#define F7	(0x16 + EXT)
#define F8	(0x17 + EXT)
#define F9	(0x18 + EXT)
#define F10	(0x19 + EXT)
#define F11	(0x1A + EXT)
#define F12	(0x1B + EXT)

/* Other nonprint character*/
#define ENTER     (0x20 + EXT)
#define TAB       (0x21 + EXT)
#define ESC       (0x22 + EXT)
#define BACKSPACE (0x23 + EXT)
#define SHIFT_L	  (0x24 + EXT)	/* L Shift	*/
#define SHIFT_R	  (0x25 + EXT)	/* R Shift	*/
#define CTRL_L	  (0x26 + EXT)	/* L Ctrl	*/
#define CTRL_R	  (0x27 + EXT)	/* R Ctrl	*/
#define ALT_L	  (0x28 + EXT)	/* L Alt	*/
#define ALT_R	  (0x29 + EXT)	/* R Alt	*/

/* ACPI keys */
#define POWER		(0x30 + EXT)	/* Power	*/
#define SLEEP		(0x31 + EXT)	/* Sleep	*/
#define WAKE		(0x32 + EXT)	/* Wake Up	*/
#define GUI_L		(0x33 + EXT)	/* L GUI	*/
#define GUI_R		(0x34 + EXT)	/* R GUI	*/
#define APPS		(0x35 + EXT)	/* APPS	*/

/* Lock keys */
#define CAPS_LOCK	(0x40 + EXT)	/* Caps Lock	*/
#define	NUM_LOCK	(0x41 + EXT)	/* Number Lock	*/
#define SCROLL_LOCK	(0x52 + EXT)	/* Scroll Lock	*/

#define      MAP_COLS	        0x3	    /* Number of columns in keymap */
#define      NR_SCAN_CODES	    0x80	/* Number of scan codes (rows in keymap) */

#define      Mask_break         0x7f    /* Scan code conversion. */
#define      Flag_break         0x80    /* ≈–∂œbit 7*/

#define      NR_KEY             32
#define	     LED_CODE	        0xED
#define	     KB_ACK		        0xFA
#define      Check(x)           ((x) & 0xFF)

struct   Key_in                 /*º¸≈Ãª∫≥Â*/
{
         int8     buffer[NR_KEY];
         int32    counts;
         int32    p_start;
         int32    p_end;
};

#endif

/* »´æ÷±‰¡ø */
int32		code_with_E0;
int32		shift_l;		         /* l shift state	*/
int32		shift_r;		         /* r shift state	*/
int32		alt_l;	    		     /* l alt state		*/
int32		alt_r;		             /* r alt state	    */
int32		ctrl_l;			         /* l ctrl state	*/
int32		ctrl_r;			         /* r ctrl state	*/
int32		caps_lock;		         /* Caps Lock		*/
int32		num_lock;		         /* Num Lock		*/
int32		scroll_lock;	         /* Scroll Lock		*/

struct  Key_in    Key_buff;                /*º¸≈Ãª∫≥Â*/

void kb_wait();
void kb_ack();
void set_leds();
int8 buff_read_keyboard();                 /*∂¡»°ª∫≥Â«¯*/
int32 keyboard_read();                     /*Ω‚Œˆº¸≈Ã…®√Ë¬Î*/
void keyboard_handler(int irq);            /*º¸≈Ã÷–∂œ¥¶¿Ì∫Ø ˝*/
void key_init();                           /*º¸≈Ã÷–∂œ≥ı ºªØ∫Ø ˝*/

