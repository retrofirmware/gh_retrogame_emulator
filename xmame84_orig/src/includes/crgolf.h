/*************************************************************************

	Kitco Crowns Golf hardware

**************************************************************************/

/*----------- defined in vidhrdw/crgolf.c -----------*/

extern data8_t *crgolf_color_select;
extern data8_t *crgolf_screen_flip;
extern data8_t *crgolf_screen_select;
extern data8_t *crgolf_screenb_enable;
extern data8_t *crgolf_screena_enable;

WRITE8_HANDLER( crgolf_videoram_bit0_w );
WRITE8_HANDLER( crgolf_videoram_bit1_w );
WRITE8_HANDLER( crgolf_videoram_bit2_w );

READ8_HANDLER( crgolf_videoram_bit0_r );
READ8_HANDLER( crgolf_videoram_bit1_r );
READ8_HANDLER( crgolf_videoram_bit2_r );

PALETTE_INIT( crgolf );
VIDEO_START( crgolf );
VIDEO_UPDATE( crgolf );
