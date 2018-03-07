/****************************************************
   Pit&Run - Taito 1984

 driver by  Tomasz Slanina and	Pierpaolo Prazzoli


TODO:

 - analog sound
   writes to $a8xx triggering analog sound :
   	$a800 - drivers are gettin into the cars
   	$a801 - collisions
   	$a802 - same as above
   	$a803 - slide on water
   	$a804 - accelerate
   	$a807 - analog sound reset


-----------------------------------------------------
$8101 B - course
$8102 B - trial
$8492 B - fuel
$84f6 B - lap
$84c1 W - time
-----------------------------------------------------

N4200374A

K1000232A
            A11_17     2128  PR9
           (68705P5)         PR10
                             PR11
     SW1                     PR12
                        Z80
                                      clr.1
                        PR8           clr.2

               PR6                    clr.3
               PR7
                              2114
                              2114

K1000231A

    2114 2114
    PR13
                Z80

          8910 8910
   5MHz

K1000233A

  2125      2125        2128
  2125      2125        2128
  2125      2125        PR4
  2125      2125        PR5
  2125      2125

                             2114
     PR1                     2114
     PR2
     PR3
*/

#include "driver.h"
#include "vidhrdw/generic.h"

WRITE8_HANDLER (pitnrun_68705_portA_w);
WRITE8_HANDLER (pitnrun_68705_portB_w);

READ8_HANDLER (pitnrun_68705_portA_r);
READ8_HANDLER (pitnrun_68705_portB_r);
READ8_HANDLER (pitnrun_68705_portC_r);

MACHINE_INIT( pitnrun );

READ8_HANDLER( pitnrun_mcu_data_r );
READ8_HANDLER( pitnrun_mcu_status_r );
WRITE8_HANDLER( pitnrun_mcu_data_w );

extern UINT8* videoram2;

WRITE8_HANDLER( pitnrun_videoram_w );
WRITE8_HANDLER( pitnrun_videoram2_w );
WRITE8_HANDLER(pitnrun_ha_w);
WRITE8_HANDLER(pitnrun_h_heed_w);
WRITE8_HANDLER(pitnrun_v_heed_w);
WRITE8_HANDLER(pitnrun_color_select_w);
WRITE8_HANDLER( pitnrun_char_bank_select );
WRITE8_HANDLER( pitnrun_scroll_w );
READ8_HANDLER( pitnrun_videoram_r );
READ8_HANDLER( pitnrun_videoram2_r );

PALETTE_INIT(pitnrun);
VIDEO_START(pitnrun);
VIDEO_UPDATE(pitnrun);

static int pitnrun_nmi;

static INTERRUPT_GEN( pitnrun_nmi_source )
{
	 if(pitnrun_nmi) cpunum_set_input_line(0,INPUT_LINE_NMI, PULSE_LINE)	;
}

static WRITE8_HANDLER( nmi_enable_w )
{
        pitnrun_nmi=data&1;
}

static WRITE8_HANDLER(pitnrun_hflip_w)
{
	flip_screen_x_set(data);
}

static WRITE8_HANDLER(pitnrun_vflip_w)
{
	flip_screen_y_set(data);
}

static ADDRESS_MAP_START( readmem, ADDRESS_SPACE_PROGRAM, 8 )
	AM_RANGE(0x0000, 0x7fff) AM_READ(MRA8_ROM)
	AM_RANGE(0x8000, 0x87ff) AM_READ(MRA8_RAM)
	AM_RANGE(0x8800, 0x8fff) AM_READ(pitnrun_videoram_r)
	AM_RANGE(0x9000, 0x9fff) AM_READ(pitnrun_videoram2_r)
	AM_RANGE(0xa000, 0xa0ff) AM_READ(spriteram_r)
	AM_RANGE(0xa800, 0xa800) AM_READ(input_port_0_r)
	AM_RANGE(0xb000, 0xb000) AM_READ(input_port_1_r)
	AM_RANGE(0xb800, 0xb800) AM_READ(input_port_2_r)
	AM_RANGE(0xd800, 0xd800) AM_READ(pitnrun_mcu_status_r)
	AM_RANGE(0xd000, 0xd000) AM_READ(pitnrun_mcu_data_r)
	AM_RANGE(0xf000, 0xf000) AM_READ(watchdog_reset_r)
ADDRESS_MAP_END

static ADDRESS_MAP_START( writemem, ADDRESS_SPACE_PROGRAM, 8 )
	AM_RANGE(0x0000, 0x7fff) AM_WRITE(MWA8_ROM)
	AM_RANGE(0x8000, 0x87ff) AM_WRITE(MWA8_RAM)
	AM_RANGE(0x8800, 0x8fff) AM_WRITE(pitnrun_videoram_w) AM_BASE(&videoram) AM_SIZE(&videoram_size)
	AM_RANGE(0x9000, 0x9fff) AM_WRITE(pitnrun_videoram2_w) AM_BASE(&videoram2)
	AM_RANGE(0xa000, 0xa0ff) AM_WRITE(spriteram_w) AM_BASE(&spriteram) AM_SIZE(&spriteram_size)
	AM_RANGE(0xa800, 0xa807) AM_WRITE(MWA8_NOP) /* Analog Sound */
	AM_RANGE(0xb000, 0xb000) AM_WRITE(nmi_enable_w)
	AM_RANGE(0xb001, 0xb001) AM_WRITE(pitnrun_color_select_w)
	AM_RANGE(0xb004, 0xb004) AM_WRITE(MWA8_NOP)/* COLOR SEL 2 - not used ?*/
	AM_RANGE(0xb005, 0xb005) AM_WRITE(pitnrun_char_bank_select)
	AM_RANGE(0xb006, 0xb006) AM_WRITE(pitnrun_hflip_w)
	AM_RANGE(0xb007, 0xb007) AM_WRITE(pitnrun_vflip_w)
	AM_RANGE(0xb800, 0xb800) AM_WRITE(soundlatch_w)
	AM_RANGE(0xc800, 0xc801) AM_WRITE(pitnrun_scroll_w)
	AM_RANGE(0xc802, 0xc802) AM_WRITE(MWA8_NOP)/* VP(VF?)MCV - not used ?*/
	AM_RANGE(0xc804, 0xc804) AM_WRITE(pitnrun_mcu_data_w)
	AM_RANGE(0xc805, 0xc805) AM_WRITE(pitnrun_h_heed_w)
 	AM_RANGE(0xc806, 0xc806) AM_WRITE(pitnrun_v_heed_w)
	AM_RANGE(0xc807, 0xc807) AM_WRITE(pitnrun_ha_w)
ADDRESS_MAP_END

static ADDRESS_MAP_START( sound_writeport, ADDRESS_SPACE_IO, 8 )
	AM_RANGE(0x00, 0x00) AM_WRITE(soundlatch_clear_w)
	AM_RANGE(0x8c, 0x8c) AM_WRITE(AY8910_control_port_1_w)
	AM_RANGE(0x8d, 0x8d) AM_WRITE(AY8910_write_port_1_w)
	AM_RANGE(0x8e, 0x8e) AM_WRITE(AY8910_control_port_0_w)
	AM_RANGE(0x8f, 0x8f) AM_WRITE(AY8910_write_port_0_w)
	AM_RANGE(0x90, 0x96) AM_WRITE(MWA8_NOP)
	AM_RANGE(0x97, 0x97) AM_WRITE(MWA8_NOP)
	AM_RANGE(0x98, 0x98) AM_WRITE(MWA8_NOP)
ADDRESS_MAP_END

static ADDRESS_MAP_START( sound_readport, ADDRESS_SPACE_IO, 8 )
	AM_RANGE(0x8f, 0x8f) AM_READ(AY8910_read_port_0_r)
ADDRESS_MAP_END


static ADDRESS_MAP_START( sound_readmem, ADDRESS_SPACE_PROGRAM, 8 )
	AM_RANGE(0x0000, 0x2fff) AM_READ(MRA8_ROM)
	AM_RANGE(0x3800, 0x3bff) AM_READ(MRA8_RAM)

ADDRESS_MAP_END


static ADDRESS_MAP_START( sound_writemem, ADDRESS_SPACE_PROGRAM, 8 )
	AM_RANGE(0x0000, 0x2fff) AM_WRITE(MWA8_ROM)
	AM_RANGE(0x3800, 0x3bff) AM_WRITE(MWA8_RAM)
ADDRESS_MAP_END

static ADDRESS_MAP_START( mcu_readmem, ADDRESS_SPACE_PROGRAM, 8 )
	ADDRESS_MAP_FLAGS( AMEF_ABITS(11) )
	AM_RANGE(0x0000, 0x0000) AM_READ(pitnrun_68705_portA_r)
	AM_RANGE(0x0001, 0x0001) AM_READ(pitnrun_68705_portB_r)
	AM_RANGE(0x0002, 0x0002) AM_READ(pitnrun_68705_portC_r)
	AM_RANGE(0x0003, 0x007f) AM_READ(MRA8_RAM)
	AM_RANGE(0x0080, 0x07ff) AM_READ(MRA8_ROM)
ADDRESS_MAP_END


static ADDRESS_MAP_START( mcu_writemem, ADDRESS_SPACE_PROGRAM, 8 )
	ADDRESS_MAP_FLAGS( AMEF_ABITS(11) )
	AM_RANGE(0x0000, 0x0000) AM_WRITE(pitnrun_68705_portA_w)
	AM_RANGE(0x0001, 0x0001) AM_WRITE(pitnrun_68705_portB_w)
	AM_RANGE(0x0003, 0x007f) AM_WRITE(MWA8_RAM)
	AM_RANGE(0x0080, 0x07ff) AM_WRITE(MWA8_ROM)
ADDRESS_MAP_END

INPUT_PORTS_START( pitnrun )
	PORT_START      /* IN0 */
	PORT_BIT( 0x01, IP_ACTIVE_HIGH, IPT_COIN1  )
	PORT_BIT( 0x02, IP_ACTIVE_HIGH, IPT_SERVICE1 )
	PORT_BIT( 0x04, IP_ACTIVE_HIGH, IPT_START1 )
	PORT_BIT( 0x08, IP_ACTIVE_HIGH, IPT_START2 )
	PORT_BIT( 0x10, IP_ACTIVE_HIGH, IPT_UNKNOWN )
	PORT_BIT( 0x20, IP_ACTIVE_HIGH, IPT_UNKNOWN )
	PORT_BIT( 0x40, IP_ACTIVE_HIGH, IPT_UNKNOWN )
	PORT_BIT( 0x80, IP_ACTIVE_HIGH, IPT_UNKNOWN )

	PORT_START		/* DSW0 */
	PORT_DIPNAME( 0x07, 0x01, DEF_STR( Coinage ) )
	PORT_DIPSETTING(    0x00, DEF_STR( 2C_1C ) )
	PORT_DIPSETTING(    0x01, DEF_STR( 1C_1C ) )
	PORT_DIPSETTING(    0x02, DEF_STR( 1C_2C ) )
	PORT_DIPSETTING(    0x03, DEF_STR( 1C_3C ) )
	PORT_DIPSETTING(    0x04, DEF_STR( 1C_4C ) )
	PORT_DIPSETTING(    0x05, DEF_STR( 1C_5C ) )
	PORT_DIPSETTING(    0x06, DEF_STR( 1C_6C ) )
	PORT_DIPSETTING(    0x07, DEF_STR( 1C_7C ) )
	PORT_BIT( 0x08, IP_ACTIVE_HIGH, IPT_UNKNOWN )
	PORT_BIT( 0x10, IP_ACTIVE_HIGH, IPT_UNKNOWN )
	PORT_DIPNAME( 0x20, 0x00, "Gasoline Count" )
	PORT_DIPSETTING(    0x00, "10 Up or 10 Down" )
	PORT_DIPSETTING(    0x20, "20 Up or 20 Down" )
	PORT_DIPNAME( 0x40, 0x00, DEF_STR( Cabinet ) )
	PORT_DIPSETTING(    0x00, DEF_STR( Upright ) )
	PORT_DIPSETTING(    0x40, DEF_STR( Cocktail ) )
	PORT_BITX(    0x80, 0x00, IPT_DIPSWITCH_NAME | IPF_CHEAT, "No Hit", IP_KEY_NONE, IP_JOY_NONE )
	PORT_DIPSETTING(    0x00, DEF_STR( Off ) )
	PORT_DIPSETTING(    0x80, DEF_STR( On ) )

	PORT_START	/* IN 1 */
	PORT_BIT( 0x01, IP_ACTIVE_HIGH, IPT_JOYSTICK_LEFT    | IPF_8WAY )
	PORT_BIT( 0x02, IP_ACTIVE_HIGH, IPT_JOYSTICK_RIGHT  | IPF_8WAY )
	PORT_BIT( 0x04, IP_ACTIVE_HIGH, IPT_JOYSTICK_DOWN  | IPF_8WAY )
	PORT_BIT( 0x08, IP_ACTIVE_HIGH, IPT_JOYSTICK_UP | IPF_8WAY )
	PORT_BIT( 0x10, IP_ACTIVE_HIGH, IPT_BUTTON1 )
	PORT_BIT( 0x20, IP_ACTIVE_HIGH, IPT_BUTTON2 )
	PORT_BIT( 0x40, IP_ACTIVE_HIGH, IPT_UNKNOWN )
	PORT_BIT( 0x80, IP_ACTIVE_HIGH, IPT_UNKNOWN )
INPUT_PORTS_END


static struct GfxLayout spritelayout =
{
	16,16,
	RGN_FRAC(1,3),
	3,
	{ 0,RGN_FRAC(1,3), RGN_FRAC(2,3) },
	{ 0, 1, 2, 3, 4, 5, 6, 7,
	  8*8+0, 8*8+1, 8*8+2, 8*8+3, 8*8+4, 8*8+5, 8*8+6, 8*8+7 },
	{ 0*8, 1*8, 2*8, 3*8, 4*8, 5*8, 6*8, 7*8,
	  16*8, 17*8, 18*8, 19*8, 20*8, 21*8, 22*8, 23*8 },
	32*8
};

static struct GfxLayout charlayout =
{
	8,8,
	RGN_FRAC(1,2),
	4,
	{RGN_FRAC(1,2),RGN_FRAC(1,2)+4,0,4},
	{ STEP4(0,1), STEP4(8,1) },
	{ STEP8(0,8*2) },
	8*8*2
};

static struct AY8910interface ay8910_interface =
{
	2,
	18432000/12,
	{ 50, 50 },
	{ soundlatch_r, soundlatch_r },
	{ soundlatch_r, soundlatch_r },
	{ 0, 0 },
	{ 0, 0 }
};

static struct GfxDecodeInfo gfxdecodeinfo[] =
{
	{ REGION_GFX3, 0, &charlayout,   64,2 },
	{ REGION_GFX2, 0, &charlayout,   32,2 },
	{ REGION_GFX1, 0, &spritelayout,   0, 4},
	{ -1 }
};

static MACHINE_DRIVER_START( pitnrun )
	MDRV_CPU_ADD(Z80,8000000/2)		 /* ? MHz */
	MDRV_CPU_PROGRAM_MAP(readmem,writemem)
	MDRV_CPU_VBLANK_INT(pitnrun_nmi_source,1)

	MDRV_FRAMES_PER_SECOND(60)
	MDRV_VBLANK_DURATION(DEFAULT_60HZ_VBLANK_DURATION)

	MDRV_CPU_ADD(Z80, 10000000/4)     /* 2.5 MHz */

	MDRV_CPU_FLAGS(CPU_AUDIO_CPU)
	MDRV_CPU_PROGRAM_MAP(sound_readmem,sound_writemem)
	MDRV_CPU_IO_MAP(sound_readport,sound_writeport)
	MDRV_CPU_VBLANK_INT(irq0_line_hold,1)

	MDRV_CPU_ADD(M68705,2000000)
	MDRV_CPU_PROGRAM_MAP(mcu_readmem,mcu_writemem)

	MDRV_MACHINE_INIT(pitnrun)

	MDRV_INTERLEAVE(100)

	MDRV_VIDEO_ATTRIBUTES(VIDEO_TYPE_RASTER )
	MDRV_SCREEN_SIZE(256, 256)
	MDRV_VISIBLE_AREA(0*8, 32*8-1, 2*8, 30*8-1)

	MDRV_GFXDECODE(gfxdecodeinfo)
	MDRV_PALETTE_LENGTH(32*3)
	MDRV_PALETTE_INIT(pitnrun)
	MDRV_VIDEO_START(pitnrun)
	MDRV_VIDEO_UPDATE(pitnrun)
	MDRV_SOUND_ADD(AY8910, ay8910_interface)

MACHINE_DRIVER_END


ROM_START( pitnrun )
	ROM_REGION( 0x010000, REGION_CPU1, 0 )
	ROM_LOAD( "pr12",  0x00000, 0x02000, CRC(587a7b85) SHA1(f200ff9b706e13760a23e0187c6bffe496af0087) )
	ROM_LOAD( "pr11",  0x02000, 0x02000, CRC(270cd6dd) SHA1(ad42562e18aa30319fc55c201e5507e8734a5b4d) )
	ROM_LOAD( "pr10",  0x04000, 0x02000, CRC(65d92d89) SHA1(4030ccdb4d84e69c256e95431ee5a18cffeae5c0) )
	ROM_LOAD( "pr9",   0x06000, 0x02000, CRC(3155286d) SHA1(45af8cb81d70f2e30b52bbc7abd9f8d15231735f) )

	ROM_REGION( 0x010000, REGION_CPU2, 0 )
	ROM_LOAD( "pr13",  0x00000, 0x01000, CRC(fc8fd05c) SHA1(f40cc9c6fff6bda8411f4d638a0f5c5915aa3746) )

	ROM_REGION( 0x010000, REGION_CPU3, 0 )
	ROM_LOAD( "a11_17.3a",	0x0000, 0x800, CRC(e7d5d6e1) SHA1(c1131d6fcc36926e287be26090a3c89f22feaa35) )

	ROM_REGION( 0x06000, REGION_GFX1, 0 )
	ROM_LOAD( "pr1",  0x000000, 0x002000, CRC(c3b3131e) SHA1(ed0463e7eef452d7fbdcb031f9477825e9780943) )
	ROM_LOAD( "pr2",  0x002000, 0x002000, CRC(2fa1682a) SHA1(9daefb525fd69f0d9a45ff27e89865545e177a5a) )
	ROM_LOAD( "pr3",  0x004000, 0x002000, CRC(e678fe39) SHA1(134e36fd30bf3cf5884732f3455ca4d9dab6b665) )

	ROM_REGION( 0x4000, REGION_GFX2, 0 )
	ROM_LOAD( "pr4",  0x00000, 0x002000, CRC(fbae3504) SHA1(ce799dfd653462c0814e7530f3f8a686ab0ad7f4) )
	ROM_LOAD( "pr5",  0x02000, 0x002000, CRC(c9177180) SHA1(98c8f8f586b78b88dba254bd662642ee27f9b131) )

	ROM_REGION( 0x2000, REGION_GFX3, 0 )
	ROM_LOAD( "pr6",  0x00000, 0x001000, CRC(c53cb897) SHA1(81a73e6031b52fa45ec507ff4264b14474ef42a2) )
	ROM_LOAD( "pr7",  0x01000, 0x001000, CRC(7cdf9a55) SHA1(404dface7e09186e486945981e39063929599efc) )

	ROM_REGION( 0x2000, REGION_USER1, 0 )
	ROM_LOAD( "pr8",	0x0000, 0x2000, CRC(8e346d10) SHA1(1362ce4362c2d28c48fbd8a33da0cec5ef8e321f) )

	ROM_REGION( 0x0060, REGION_PROMS, 0 )
	ROM_LOAD( "clr.1",  0x0000, 0x0020, CRC(643012f4) SHA1(4a0c9766b9da456e39ce379ad62d695bf82413b0) )
	ROM_LOAD( "clr.2",  0x0020, 0x0020, CRC(50705f02) SHA1(a3d348678fd66f37c7a0d29af88f40740918b8d3) )
	ROM_LOAD( "clr.3",  0x0040, 0x0020, CRC(25e70e5e) SHA1(fdb9c69e9568a725dd0e3ac25835270fb4f49280) )
ROM_END

GAMEX( 1984, pitnrun, 0, pitnrun, pitnrun, 0, ROT90, "Taito Corporation", "Pit & Run", GAME_IMPERFECT_SOUND )

