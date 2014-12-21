/**
 *  @author Joao Cardoso (jcard@fe.up.pt) ????
 *  Added by pfs@fe.up.pt
 */

/** Format of a xpm-like (there is a real xpm format) pic:
 * <pre>
 * static char *picture_name[] = {
 * "number_of_x_pixels number_of_y_pixels number_of_colors",
 * "one_char_symbol the_char_symbol_color",
 * ... exactly number_of_colors lines as above
 * "any of the above one_char_symbol, exactly number_of_x_pixels times",
 * ... exactly number_of_y_pixels lines as above
 * };
 *
 * Example:
 *
 * static char *pic1[] = {  // the name os the picture, "pic1" in this case
 * "32 13 4",               // number of pixels in the x and y dimension,
 *                          //   and the number of colors, which follows.
 * ". 0",                   // mapping between symbols and colors; in this
 *                          //   case, the "." will be mapped to color 0
 * "x 2",                   // and the "x" to color 2
 * ...                      // the next symbol/color pairs
 * "................................", // first row, exactly 32 pixels,
 *                                     // all color 0, BLACK
 * "..............xxx...............", // next row has three GREEN pixels
 *                                     // at the center
 * </pre>
 * Colors names/colors number equivalence are at c:/djgpp/include/conio.h
 *
 * Any real xpm picture can be read, as long as there are only 16
 * colors on it, and the colors are the ones available in conio.h.
 *
 *  To use other/more colors than the basic ones, the graphic card
 *  pallete must be programmed.
 *
 */

static char *folder_selected[] = {
		"36 31 5",
		". 0",
		"+ 14",
		"# 15",
		"o 8",
		"$ 3",
		"++++++++++++++++++++++++++++++++++++",
		"+..................................+",
		"+..oooooooo........................+",
		"+..+++++++++o......................+",
		"+..++++++++++o.....................+",
		"+..+++++++++++o##########..........+",
		"+..++++++++++++o##########.........+",
		"+..+++++++++++++ooooooooooo........+",
		"+..+++++++++++++o###########.......+",
		"+..++++++++++++++o###########......+",
		"+..+++++++++++++++o###########.....+",
		"+..+++++++++++++++o############....+",
		"+..+++++++++++++++++ooooooooooo....+",
		"+..++++++++++++++++++++++++++++++..+",
		"+..++++++++++++++++++++++++++++++..+",
		"+..++++++++++++++++++++++++++++++..+",
		"+..++++++++++++++++++++++++++++++..+",
		"+..++++++++++++++++++++++++++++++..+",
		"+..++++++++++++++++++++++++++++++..+",
		"+..++++++++++++++++++++++++++++++..+",
		"+..++++++++++++++++++++++++++++++..+",
		"+..++++++++++++++++++++++++++++++..+",
		"+..++++++++++++++++++++++++++++++..+",
		"+..++++++++++++++++++++++++++++++..+",
		"+..++++++++++++++++++++++++++++++..+",
		"+..++++++++++++++++++++++++++++++..+",
		"+..++++++++++++++++++++++++++++++..+",
		"+..++++++++++++++++++++++++++++++..+",
		"+..++++++++++++++++++++++++++++++..+",
		"+..................................+",
		"++++++++++++++++++++++++++++++++++++",
};

static char *folder[] = {
		"36 31 5",
		". 0",
		"+ 14",
		"# 15",
		"o 8",
		"$ 3",
		"....................................",
		"....................................",
		"...oooooooo.........................",
		"...+++++++++o.......................",
		"...++++++++++o......................",
		"...+++++++++++o##########...........",
		"...++++++++++++o##########..........",
		"...+++++++++++++ooooooooooo.........",
		"...+++++++++++++o###########........",
		"...++++++++++++++o###########.......",
		"...+++++++++++++++o###########......",
		"...+++++++++++++++o############.....",
		"...+++++++++++++++++ooooooooooo.....",
		"...++++++++++++++++++++++++++++++...",
		"...++++++++++++++++++++++++++++++...",
		"...++++++++++++++++++++++++++++++...",
		"...++++++++++++++++++++++++++++++...",
		"...++++++++++++++++++++++++++++++...",
		"...++++++++++++++++++++++++++++++...",
		"...++++++++++++++++++++++++++++++...",
		"...++++++++++++++++++++++++++++++...",
		"...++++++++++++++++++++++++++++++...",
		"...++++++++++++++++++++++++++++++...",
		"...++++++++++++++++++++++++++++++...",
		"...++++++++++++++++++++++++++++++...",
		"...++++++++++++++++++++++++++++++...",
		"...++++++++++++++++++++++++++++++...",
		"...++++++++++++++++++++++++++++++...",
		"...++++++++++++++++++++++++++++++...",
		"....................................",
		"....................................",
};


static char *ponto[] = {
		"9 6 2",
		". 0", //background
		"% 14",
		".........",
		".........",
		".........",
		"...%%....",
		"...%%....",
		".........",
};

static char *space[] = {
		"9 6 2",
		". 0", //background
		"% 14",
		".........",
		".........",
		".........",
		".........",
		".........",
		".........",

};

static char *xpm0[] = {
		"9 6 2",
		". 0", //background
		"% 14",
		"..%%%%...",
		".%%..%%..",
		".%%%%%%..",
		".%%..%%..",
		"..%%%%...",
		".........",
};

static char *xpm1[] = {
		"9 6 2",
		". 0", //background
		"% 14",
		"...%%....",
		"..%%%....",
		"...%%....",
		"...%%....",
		".%%%%%%..",
		".........",
};

static char *xpm2[] = {
		"9 6 2",
		". 0", //background
		"% 14",
		"..%%%%...",
		".....%%..",
		"..%%%%...",
		".%%......",
		".%%%%%%..",
		".........",
};

static char *xpm3[] = {
		"9 6 2",
		". 0", //background
		"% 14",
		".%%%%%%..",
		"....%%...",
		"...%%%...",
		".....%%..",
		".%%%%%...",
		".........",
};

static char *xpm4[] = {
		"9 6 2",
		". 0", //background
		"% 14",
		".....%%..",
		".%%..%%..",
		".%%%%%%..",
		".....%%..",
		".....%%..",
		".........",
};

static char *xpm5[] = {
		"9 6 2",
		". 0", //background
		"% 14",
		".%%%%%%..",
		".%%......",
		"..%%%%...",
		".....%%..",
		".%%%%%...",
		".........",
};

static char *xpm6[] = {
		"9 6 2",
		". 0", //background
		"% 14",
		"...%%....",
		"..%%.....",
		".%%%%%...",
		".%%..%%..",
		"..%%%%...",
		".........",
};

static char *xpm7[] = {
		"9 6 2",
		". 0", //background
		"% 14",
		".%%%%%%..",
		"....%%...",
		"...%%....",
		"..%%.....",
		".%%......",
		".........",
};

static char *xpm8[] = {
		"9 6 2",
		". 0", //background
		"% 14",
		"..%%%%...",
		".%%..%%..",
		"..%%%%...",
		".%%..%%..",
		"..%%%%...",
		".........",
};


static char *xpm9[] = {
		"9 6 2",
		". 0", //background
		"% 14",
		"..%%%%...",
		".%%..%%..",
		"..%%%%...",
		"...%%....",
		"..%%.....",
		".........",
};

static char *a[] = {
		"9 6 2",
		". 0", //background
		"% 14",
		"..%%%%...",
		".%%..%%..",
		".%%%%%%..",
		".%%..%%..",
		".%%..%%..",
		".........",
};

static char *b[] = {
		"9 6 2",
		". 0", //background
		"% 14",
		".%%%%%...",
		".%%..%%..",
		".%%%%%...",
		".%%..%%..",
		".%%%%%...",
		".........",
};

static char *c[] = {
		"9 6 2",
		". 0", //background
		"% 14",
		"..%%%%...",
		".%%..%%..",
		".%%......",
		".%%..%%..",
		"..%%%%...",
		".........",
};

static char *d[] = {
		"9 6 2",
		". 0", //background
		"% 14",
		".%%%%%...",
		".%%..%%..",
		".%%..%%..",
		".%%..%%..",
		".%%%%%...",
		".........",
};

static char *e[] = {
		"9 6 2",
		". 0", //background
		"% 14",
		".%%%%%%..",
		".%%......",
		".%%%%....",
		".%%......",
		".%%%%%%..",
		".........",
};

static char *f[] = {
		"9 6 2",
		". 0", //background
		"% 14",
		".%%%%%%..",
		".%%......",
		".%%%%....",
		".%%......",
		".%%......",
		".........",
};


static char *g[] = {
		"9 6 2",
		". 0", //background
		"% 14",
		"..%%%%...",
		".%%......",
		".%%.%%%..",
		".%%..%%..",
		"..%%%%...",
		".........",
};

static char *h[] = {
		"9 6 2",
		". 0", //background
		"% 14",
		".%%..%%..",
		".%%..%%..",
		".%%%%%%..",
		".%%..%%..",
		".%%..%%..",
		".........",
};

static char *i[] = {
		"9 6 2",
		". 0", //background
		"% 14",
		".%%%%%%..",
		"...%%....",
		"...%%....",
		"...%%....",
		".%%%%%%..",
		".........",
};

static char *j[] = {
		"9 6 2",
		". 0", //background
		"% 14",
		".%%%%%%..",
		".....%%..",
		".....%%..",
		".%%..%%..",
		"..%%%%...",
		".........",
};

static char *k[] = {
		"9 6 2",
		". 0", //background
		"% 14",
		".%%..%%..",
		".%%.%%...",
		".%%%%....",
		".%%.%%...",
		".%%..%%..",
		".........",
};

static char *l[] = {
		"9 6 2",
		". 0", //background
		"% 14",
		".%%......",
		".%%......",
		".%%......",
		".%%......",
		".%%%%%%..",
		".........",
};

static char *m[] = {
		"9 6 2",
		". 0", //background
		"% 14",
		".%%...%%.",
		".%%%.%%%.",
		".%%.%.%%.",
		".%%...%%.",
		".%%...%%.",
		".........",
};

static char *n[] = {
		"9 6 2",
		". 0", //background
		"% 14",
		".%%..%%..",
		".%%%.%%..",
		".%%.%%%..",
		".%%..%%..",
		".%%..%%..",
		".........",
};

static char *o[] = {
		"9 6 2",
		". 0", //background
		"% 14",
		"..%%%%...",
		".%%..%%..",
		".%%..%%..",
		".%%..%%..",
		"..%%%%...",
		".........",
};

static char *p[] = {
		"9 6 2",
		". 0", //background
		"% 14",
		".%%%%%...",
		".%%..%%..",
		".%%%%%...",
		".%%......",
		".%%......",
		".........",
};

static char *q[] = {
		"9 6 2",
		". 0", //background
		"% 14",
		"..%%%%...",
		".%%..%%..",
		".%%.%%%..",
		".%%..%%..",
		"..%%%%%..",
		".........",
};

static char *r[] = {
		"9 6 2",
		". 0", //background
		"% 14",
		".%%%%%...",
		".%%..%%..",
		".%%%%%...",
		".%%..%%..",
		".%%..%%..",
		".........",
};

static char *s[] = {
		"9 6 2",
		". 0", //background
		"% 14",
		"..%%%%...",
		".%%......",
		"..%%%%...",
		".....%%..",
		"..%%%%...",
		".........",
};

static char *t[] = {
		"9 6 2",
		". 0", //background
		"% 14",
		".%%%%%%..",
		"...%%....",
		"...%%....",
		"...%%....",
		"...%%....",
		".........",
};

static char *u[] = {
		"9 6 2",
		". 0", //background
		"% 14",
		".%%..%%..",
		".%%..%%..",
		".%%..%%..",
		".%%..%%..",
		"..%%%%...",
		".........",
};

static char *v[] = {
		"9 6 2",
		". 0", //background
		"% 14",
		".%%..%%..",
		".%%..%%..",
		".%%..%%..",
		"..%%%%...",
		"...%%....",
		".........",
};

static char *w[] = {
		"9 6 2",
		". 0", //background
		"% 14",
		".%%...%%.",
		".%%...%%.",
		".%%.%.%%.",
		".%%%%%%%.",
		"..%%.%%..",
		".........",
};


static char *x[] = {
		"9 6 2",
		". 0", //background
		"% 14",
		".%%..%%..",
		"..%%%%...",
		"...%%....",
		"..%%%%...",
		".%%..%%..",
		".........",
};

static char *y[] = {
		"9 6 2",
		". 0", //background
		"% 14",
		".%%..%%..",
		"..%%%%...",
		"...%%....",
		"...%%....",
		"...%%....",
		".........",
};

static char *z[] = {
		"9 6 2",
		". 0", //background
		"% 14",
		".%%%%%%..",
		"....%%...",
		"...%%....",
		"..%%.....",
		".%%%%%%..",
		".........",
};

static char *cursor[] = {
		"18 20 5",
		". 0", //background
		"+ 14",
		"# 15",
		"o 8",
		"$ 3",
		"+.................",
		"++................",
		"+++...............",
		"++++..............",
		"+++++.............",
		"++++++............",
		"+++++++...........",
		"++++++++..........",
		"+++++++++.........",
		"++++++++++........",
		"+++++++++++.......",
		"++++++++++++......",
		"++++++++.++++.....",
		"++++.+++.....+....",
		"++...+++..........",
		"+.....+++.........",
		"......+++.........",
		".......+++........",
		".......+++........",
		"..................",
};

static char *pic1[] = {
		"32 13 4",
		". 0",
		"x 2",
		"o 14",
		"+ 4",
		"................................",
		"..............xxx...............",
		"............xxxxxxx.............",
		".........xxxxxx+xxxxxx..........",
		"......xxxxxxx+++++xxxxxxx.......",
		"....xxxxxxx+++++++++xxxxxxx.....",
		"....xxxxxxx+++++++++xxxxxxx.....",
		"......xxxxxxx+++++xxxxxxx.......",
		".........xxxxxx+xxxxxx..........",
		"..........ooxxxxxxxoo...........",
		".......ooo...........ooo........",
		".....ooo...............ooo......",
		"...ooo...................ooo...."
};


static char *pic2[] = {
		"32 15 3",
		". 0",
		"x 4",
		"+ 1",
		"................................",
		"..............xxx...............",
		"............xxxxxxx.............",
		".........xxxxxx+xxxxxx..........",
		"......xxxxxxx+++++xxxxxxx.......",
		"......xxxxxxx+++++xxxxxxx.......",
		"++++xxxxxxx+++++++++xxxxxxx+++++",
		"++++xxxxxxx+++++++++xxxxxxx+++++",
		"++++xxxxxxx+++++++++xxxxxxx+++++",
		"......xxxxxxx+++++xxxxxxx.......",
		"......xxxxxxx+++++xxxxxxx.......",
		".........xxxxxx+xxxxxx..........",
		"............xxxxxxx.............",
		"..............xxx...............",
		"................................",
};

static char *cross[] = {
		"32 32 2",
		". 0",
		"+ 13",
		"...............+................",
		"...............+................",
		"...............+................",
		"...............+................",
		"...............+................",
		"...............+................",
		"...............+................",
		"...............+................",
		"...............+................",
		"...............+................",
		"...............+................",
		"...............+................",
		"...............+................",
		".............++.++..............",
		"............+.....+.............",
		"...........+.......+............",
		"+++++++++++.........++++++++++++",
		"...........+.......+............",
		"............+.....+.............",
		".............++.++..............",
		"...............+................",
		"...............+................",
		"...............+................",
		"...............+................",
		"...............+................",
		"...............+................",
		"...............+................",
		"...............+................",
		"...............+................",
		"...............+................",
		"...............+................",
		"...............+................",
};


static char *pic3[] = {
		"64 32 3",
		". 0",
		"+ 1",
		"o 2",
		"..............................++++++............................",
		".........................++++++++++++++++.......................",
		"......................++++++++++++++++++++++....................",
		"....................++++++++++++++++++++++++++..................",
		".................++++++++++++++++++++++++++++++++...............",
		"...............++++++++++++++++++++++++++++++++++++.............",
		".............++++++++++++++++++++++++++++++++++++++++...........",
		"............++++++++++++++++++++++++++++++++++++++++++..........",
		"..........++++++++++++++++++++++++++++++++++++++++++++++........",
		".........++++++++++++++++++++++++++++++++++++++++++++++++.......",
		"........+++++++++++++++++++++++++++++++++++++++++++++++++.......",
		".......+++++++++++++++++++++++++++++++++++++++++++++++++++......",
		"......+++++++++++++++++++++++++++++++++++++++++++++++++++++.....",
		".....++++++++++++++++++++++++++++++++++++++++++++++++++++++.....",
		"....++++++++++++++++++++++++++++++++++++++++++++++++++++++++....",
		"...++++++++++++++++++++++++++++++++++++++++++++++++++++++++++...",
		"...++++++++++++++++++++++++++++++++++++++++++++++++++++++++++...",
		"..++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++..",
		"..++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++..",
		".++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++.",
		".+++++ooo+++++++++ooo+++++++++ooo+++++++++ooo+++++++++ooo++++++.",
		".++++ooooo+++++++ooooo+++++++ooooo+++++++ooooo+++++++ooooo+++++.",
		".+++ooooooo+++++ooooooo+++++ooooooo+++++ooooooo+++++ooooooo++++.",
		".++++ooooo+++++++ooooo+++++++ooooo+++++++ooooo+++++++ooooo+++++.",
		".+++++ooo+++++++++ooo+++++++++ooo+++++++++ooo+++++++++ooo++++++.",
		".++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++.",
		".++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++.",
		".++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++.",
		"++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++",
		"++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++",
		"++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++",
		"++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++",
};

/* this one was converted from a 32 bits colors png! */

static char * penguin[] = {
		"64 64 9",
		"  0",
		". 15",
		"+ 8",
		"@ 14",
		"# 4",
		"$ 6",
		"% 7",
		"& 9",
		"* 1",
		"                                                                ",
		"                                                                ",
		"                           +#++#&+#+                            ",
		"                        +..%......&.+++                         ",
		"                     #...+..+.+.+.#.+.+++                       ",
		"                    .*#%..+.%.&.#*+.#%.++++                     ",
		"                  #.+.#*#%..+.#*#.%#*#+.++++                    ",
		"                 .&.%......#*#.%.+.#&.+%#%++++                  ",
		"                #*#..........+.+.+.+.+.++#+++++                 ",
		"               &#.+..........%.+.&#*#&#*.+&+++++                ",
		"              +.+.............#*#.+.......#++++++               ",
		"             #+.+..............+.+..........+++++               ",
		"            +&.+%..............%+............+++++              ",
		"            ++.+#.............................+++++             ",
		"           ++.+%.............#..#..#..........+++++             ",
		"          +++.++%..........#    .    #........++++++            ",
		"          ++++.+...........#   .     #.....%..+++++++           ",
		"          ++%+#+&..........#   .     #........+++++++           ",
		"         +++#*+#..%.........#  .    #........%+++++++           ",
		"         ++++%+++..%..%......#.#..#...%..%#..+++++++++          ",
		"        +++++#+&+#.......%..................++++++++++          ",
		"        ++++*++.+++.%.#...@@@@@@@@@@@@...%.+++++++++++          ",
		"        +++++#+++%#$#.&.+.%@@@@@@@@@@...#++++++++++++++         ",
		"        +++++&+.++++*.#.....@@@@@@@@......+++++++++&+++         ",
		"       ++++++++++%#%....%....@@@@@@........+++++++++++%         ",
		"       +++++++++++#...........@@@@@.........+++++++++++         ",
		"       ++++++++++..............@@@...........+++++++++++        ",
		"      +++++++++++...............@.............+++++%+++++       ",
		"    ++++++++++++.....................%.........+++++++++++      ",
		"   ++++++++++++%.........................%..%..%++++%++++++     ",
		"  +++++++++++++...............................#.++++++++++++    ",
		" +++++++++++++%..%.........................#.....++++++++++++   ",
		"++++++++++++++........................%..%..%.+.%++%++++++++++  ",
		"++++++++++++++...................................#++%++++++++++ ",
		"    +++++++++...%..%.....................%.+.%#.%.++++++        ",
		"       ++++++%....................%...........$.#.#+#%+         ",
		"       +++++#........................%..#..+.#.%$%+&+++         ",
		"        ++++&.#.%..%....................%...*#.#...+#++         ",
		"        ++++..%...........................%..%.+.+.+&++         ",
		"        +++++...%.....%.........%...%..+..#.#..#.%.+#+          ",
		"        ++++..#...%......%...............&.*.+.*#$#&++          ",
		"         +++..*#...%.........%.....#..%...#.%.#%.+..++          ",
		"         +++.#...#..............%...%..#..&.#*#.+.+++           ",
		"          ++.%.&...%..%..%..........#..*#..+..+.#%.++           ",
		"          ++..#..+..........%...%..$..%..+..&#*.+.+++           ",
		"           +*.+.....%............#..$.#...+.#.+.+%.+            ",
		"           +...%.+.#..%.%..#.%.#..%.#.*#%..&.+.+.+++            ",
		"            +.+.......#..%.....%...%.#..&#$#%.+.+.+             ",
		"            #..%#*#%....#..+..$..+..+.&#.+.+.+%+#&              ",
		"             +.....#*#$.+...%.#...+....+.%#*#.+.+               ",
		"              +.+.&..%..%.+.#.&.+..&#+.+.+.+.++++               ",
		"               %..+.#.+.+.+.*#..%#.$.+.&#*#&#%.+                ",
		"                +.%#*#%#$.%#.+.+.+.+%#$#+%#*+++                 ",
		"                 @#.#$#%++.+.%.+.&.#*#%+#$##$#                  ",
		"          .@.@@@@@@@@@@$#.++.+.#.+.+%#$......@@@@@@@            ",
		"        @@@@@.@.@@@@@@@@@$.+$#&+.+.+@@..@....@.@@@$@@$          ",
		"       @@@@@@.@@.@$@$@$$@$@+%#$#&#+@@.@..@@.@.@@$@@$$$$+        ",
		"      @@@@@@@@@@@@@$@$@$@$$$+%+.+%$$@@$@@.@.@$@$@$$@$$$$        ",
		"       @@@@$@$@$@$$@$$$$$$$#++++++#$@$@$$$$@$$@$$$$$$$$+        ",
		"        @$@@$@$@$@$$$$$$$$          $$$$@$$$$$$$$$$$$$+         ",
		"          $$@$$$$$$$$$$$               $$$$$$$$$$$$+            ",
		"                                                                ",
		"                                                                ",
		"                                                                "};
