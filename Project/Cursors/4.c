/* GIMP RGBA C-Source image dump (4.c) */

static const struct {
  guint  	 width;
  guint  	 height;
  guint  	 bytes_per_pixel; /* 2:RGB16, 3:RGB, 4:RGBA */ 
  guint8 	 pixel_data[31 * 31 * 4 + 1];
} gimp_image = {
  31, 31, 4,
  "\366\366\365\000\366\366\365\000\366\366\365\000\366\366\365\000\366\366\365\000\366"
  "\366\365\000\366\366\365\000\366\366\365\000\366\366\365\000\366\366\365\000\366\366"
  "\365\000\366\366\365\000\366\366\365\000\366\366\365\000\000\000\000\010\000\000\000\020\000\000\000"
  "\010\366\366\365\000\366\366\365\000\366\366\365\000\366\366\365\000\366\366\365\000"
  "\366\366\365\000\366\366\365\000\366\366\365\000\366\366\365\000\366\366\365\000\366"
  "\366\365\000\366\366\365\000\366\366\365\000\366\366\365\000\366\366\365\000\366\366"
  "\365\000\366\366\365\000\366\366\365\000\366\366\365\000\366\366\365\000\366\366\365"
  "\000\366\366\365\000\366\366\365\000\366\366\365\000\366\366\365\000\366\366\365\000"
  "\366\366\365\000\000\000\000\024\000\000\000J\000\000\000t\000\000\000J\000\000\000\024\366\366\365\000\366\366"
  "\365\000\366\366\365\000\366\366\365\000\366\366\365\000\366\366\365\000\366\366\365"
  "\000\366\366\365\000\366\366\365\000\366\366\365\000\366\366\365\000\366\366\365\000"
  "\366\366\365\000\366\366\365\000\366\366\365\000\366\366\365\000\366\366\365\000\366"
  "\366\365\000\366\366\365\000\366\366\365\000\366\366\365\000\366\366\365\000\366\366"
  "\365\000\366\366\365\000\366\366\365\000\000\000\000\024\000\000\000_\000\000\000\307\377\377\377"
  "\377\000\000\000\307\000\000\000_\000\000\000\024\366\366\365\000\366\366\365\000\366\366\365\000"
  "\366\366\365\000\366\366\365\000\366\366\365\000\366\366\365\000\366\366\365\000\366"
  "\366\365\000\366\366\365\000\366\366\365\000\366\366\365\000\366\366\365\000\366\366"
  "\365\000\366\366\365\000\366\366\365\000\366\366\365\000\366\366\365\000\366\366\365"
  "\000\366\366\365\000\366\366\365\000\366\366\365\000\366\366\365\000\000\000\000\024\000\000\000"
  "_\000\000\000\316\377\377\377\377\377\377\377\377\377\377\377\377\000\000\000\317\000\000"
  "\000_\000\000\000\024\366\366\365\000\366\366\365\000\366\366\365\000\366\366\365\000\366"
  "\366\365\000\366\366\365\000\366\366\365\000\366\366\365\000\366\366\365\000\366\366"
  "\365\000\366\366\365\000\366\366\365\000\366\366\365\000\366\366\365\000\366\366\365"
  "\000\366\366\365\000\366\366\365\000\366\366\365\000\366\366\365\000\366\366\365\000"
  "\366\366\365\000\000\000\000\024\000\000\000_\000\000\000\316\377\377\377\377\377\377\377\377"
  "\377\377\377\377\377\377\377\377\377\377\377\377\000\000\000\317\000\000\000_\000\000\000\024"
  "\366\366\365\000\366\366\365\000\366\366\365\000\366\366\365\000\366\366\365\000\366"
  "\366\365\000\366\366\365\000\366\366\365\000\366\366\365\000\366\366\365\000\366\366"
  "\365\000\366\366\365\000\366\366\365\000\366\366\365\000\366\366\365\000\366\366\365"
  "\000\366\366\365\000\366\366\365\000\366\366\365\000\000\000\000\024\000\000\000_\000\000\000\316\377"
  "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
  "\377\377\377\377\377\377\377\377\377\000\000\000\317\000\000\000_\000\000\000\024\366\366\365"
  "\000\366\366\365\000\366\366\365\000\366\366\365\000\366\366\365\000\366\366\365\000"
  "\366\366\365\000\366\366\365\000\366\366\365\000\366\366\365\000\366\366\365\000\366"
  "\366\365\000\366\366\365\000\366\366\365\000\366\366\365\000\366\366\365\000\366\366"
  "\365\000\000\000\000\010\000\000\000J\000\000\000\304\377\377\377\377\377\377\377\377\377\377"
  "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
  "\377\377\377\377\377\377\377\377\000\000\000\304\000\000\000J\000\000\000\014\366\366\365\000"
  "\366\366\365\000\366\366\365\000\366\366\365\000\366\366\365\000\366\366\365\000\366"
  "\366\365\000\366\366\365\000\366\366\365\000\366\366\365\000\366\366\365\000\366\366"
  "\365\000\366\366\365\000\366\366\365\000\366\366\365\000\366\366\365\000\000\000\000\020\000"
  "\000\000n\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
  "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
  "\377\377\377\377\377\377\377\377\377\000\000\000n\000\000\000\020\366\366\365\000\366\366"
  "\365\000\366\366\365\000\366\366\365\000\366\366\365\000\366\366\365\000\366\366\365"
  "\000\366\366\365\000\366\366\365\000\366\366\365\000\366\366\365\000\366\366\365\000"
  "\366\366\365\000\366\366\365\000\000\000\000\010\000\000\000\020\000\000\000\020\000\000\000A\000\000\000\216"
  "\000\000\000\260\000\000\000\303\000\000\000\354\377\377\377\377\377\377\377\377\377\377\377"
  "\377\000\000\000\354\000\000\000\303\000\000\000\262\000\000\000\216\000\000\000A\000\000\000\024\000\000\000\020\000\000"
  "\000\010\366\366\365\000\366\366\365\000\366\366\365\000\366\366\365\000\366\366\365"
  "\000\366\366\365\000\366\366\365\000\366\366\365\000\366\366\365\000\366\366\365\000"
  "\366\366\365\000\000\000\000\024\000\000\000J\000\000\000m\000\000\000>\000\000\000\024\000\000\000\033\000\000\000#\000\000"
  "\000E\000\000\000\304\377\377\377\377\377\377\377\377\377\377\377\377\000\000\000\304\000"
  "\000\000E\000\000\000&\000\000\000\033\000\000\000\024\000\000\000>\000\000\000m\000\000\000J\000\000\000\024\366\366\365"
  "\000\366\366\365\000\366\366\365\000\366\366\365\000\366\366\365\000\366\366\365\000"
  "\366\366\365\000\366\366\365\000\366\366\365\000\000\000\000\024\000\000\000_\000\000\000\303\377"
  "\377\377\377\000\000\000\216\000\000\000\033\366\366\365\000\366\366\365\000\000\000\000#\000\000\000"
  "\271\377\377\377\377\377\377\377\377\377\377\377\377\000\000\000\272\000\000\000&\366"
  "\366\365\000\366\366\365\000\000\000\000\033\000\000\000\216\377\377\377\377\000\000\000\303\000\000"
  "\000_\000\000\000\024\366\366\365\000\366\366\365\000\366\366\365\000\366\366\365\000\366"
  "\366\365\000\366\366\365\000\366\366\365\000\000\000\000\024\000\000\000_\000\000\000\316\377\377"
  "\377\377\377\377\377\377\000\000\000\262\000\000\000#\366\366\365\000\366\366\365\000\000\000"
  "\000#\000\000\000\271\377\377\377\377\377\377\377\377\377\377\377\377\000\000\000\272\000"
  "\000\000&\366\366\365\000\366\366\365\000\000\000\000#\000\000\000\260\377\377\377\377\377\377"
  "\377\377\000\000\000\316\000\000\000_\000\000\000\024\366\366\365\000\366\366\365\000\366\366\365"
  "\000\366\366\365\000\366\366\365\000\000\000\000\024\000\000\000_\000\000\000\316\377\377\377\377"
  "\377\377\377\377\377\377\377\377\000\000\000\303\000\000\000A\000\000\000#\000\000\000#\000\000\000A\000"
  "\000\000\303\377\377\377\377\377\377\377\377\377\377\377\377\000\000\000\303\000\000\000"
  "A\000\000\000#\000\000\000#\000\000\000A\000\000\000\303\377\377\377\377\377\377\377\377\377\377"
  "\377\377\000\000\000\317\000\000\000_\000\000\000\024\366\366\365\000\366\366\365\000\366\366\365"
  "\000\000\000\000\024\000\000\000_\000\000\000\316\377\377\377\377\377\377\377\377\377\377\377"
  "\377\377\377\377\377\000\000\000\354\000\000\000\303\000\000\000\271\000\000\000\271\000\000\000\303\000"
  "\000\000\354\377\377\377\377\377\377\377\377\377\377\377\377\000\000\000\354\000\000\000"
  "\303\000\000\000\271\000\000\000\271\000\000\000\303\000\000\000\354\377\377\377\377\377\377\377"
  "\377\377\377\377\377\377\377\377\377\000\000\000\317\000\000\000_\000\000\000\024\366\366\365"
  "\000\000\000\000\010\000\000\000J\000\000\000\307\377\377\377\377\377\377\377\377\377\377\377"
  "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
  "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
  "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
  "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
  "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\000\000"
  "\000\307\000\000\000M\000\000\000\014\000\000\000\020\000\000\000t\377\377\377\377\200\200\200\377\200"
  "\200\200\377\200\200\200\377\200\200\200\377\200\200\200\377\200\200\200"
  "\377\200\200\200\377\200\200\200\377\200\200\200\377\200\200\200\377\200"
  "\200\200\377\200\200\200\377\200\200\200\377\200\200\200\377\200\200\200"
  "\377\200\200\200\377\200\200\200\377\200\200\200\377\200\200\200\377\200"
  "\200\200\377\200\200\200\377\200\200\200\377\200\200\200\377\200\200\200"
  "\377\200\200\200\377\377\377\377\377\000\000\000t\000\000\000\024\000\000\000\010\000\000\000J\000\000"
  "\000\307\377\377\377\377\231\231\230\377\230\231\231\377\230\230\231\377\377"
  "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
  "\377\377\377\377\377\377\377\377\377\377\377\377\377\230\230\231\377\377"
  "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
  "\377\377\377\377\377\377\377\377\377\377\377\377\377\230\230\231\377\231"
  "\231\231\377\231\231\230\377\377\377\377\377\000\000\000\307\000\000\000M\000\000\000\014\366"
  "\366\365\000\000\000\000\024\000\000\000_\000\000\000\317\377\377\377\377\262\263\263\377\262"
  "\262\263\377\377\377\377\377\000\000\000\354\000\000\000\304\000\000\000\272\000\000\000\272\000\000"
  "\000\304\000\000\000\354\377\377\377\377\224\224\224\377\377\377\377\377\000\000\000\354"
  "\000\000\000\304\000\000\000\272\000\000\000\272\000\000\000\304\000\000\000\354\377\377\377\377\262\262"
  "\262\377\263\263\263\377\377\377\377\377\000\000\000\320\000\000\000_\000\000\000\024\366\366"
  "\365\000\366\366\365\000\366\366\365\000\000\000\000\024\000\000\000_\000\000\000\317\377\377\377"
  "\377\315\314\315\377\377\377\377\377\000\000\000\304\000\000\000E\000\000\000&\000\000\000&\000\000\000"
  "E\000\000\000\304\377\377\377\377\236\236\236\377\377\377\377\377\000\000\000\304\000\000"
  "\000E\000\000\000&\000\000\000&\000\000\000E\000\000\000\303\377\377\377\377\314\315\315\377\377\377"
  "\377\377\000\000\000\320\000\000\000b\000\000\000\024\366\366\365\000\366\366\365\000\366\366\365"
  "\000\366\366\365\000\366\366\365\000\000\000\000\024\000\000\000_\000\000\000\317\377\377\377\377"
  "\377\377\377\377\000\000\000\262\000\000\000#\366\366\365\000\366\366\365\000\000\000\000#\000\000"
  "\000\271\377\377\377\377\247\247\247\377\377\377\377\377\000\000\000\272\000\000\000&\366"
  "\366\365\000\366\366\365\000\000\000\000#\000\000\000\262\377\377\377\377\377\377\377\377"
  "\000\000\000\317\000\000\000b\000\000\000\024\366\366\365\000\366\366\365\000\366\366\365\000\366"
  "\366\365\000\366\366\365\000\366\366\365\000\366\366\365\000\000\000\000\024\000\000\000_\000\000"
  "\000\304\377\377\377\377\000\000\000\216\000\000\000\033\366\366\365\000\366\366\365\000\000\000"
  "\000#\000\000\000\271\377\377\377\377\261\261\261\377\377\377\377\377\000\000\000\272\000"
  "\000\000&\366\366\365\000\366\366\365\000\000\000\000\033\000\000\000\216\377\377\377\377\000\000"
  "\000\304\000\000\000_\000\000\000\024\366\366\365\000\366\366\365\000\366\366\365\000\366\366"
  "\365\000\366\366\365\000\366\366\365\000\366\366\365\000\366\366\365\000\366\366\365"
  "\000\000\000\000\024\000\000\000J\000\000\000n\000\000\000A\000\000\000\024\000\000\000\033\000\000\000#\000\000\000A\000\000\000\303"
  "\377\377\377\377\272\273\273\377\377\377\377\377\000\000\000\303\000\000\000A\000\000\000#"
  "\000\000\000\033\000\000\000\024\000\000\000A\000\000\000n\000\000\000J\000\000\000\024\366\366\365\000\366\366\365"
  "\000\366\366\365\000\366\366\365\000\366\366\365\000\366\366\365\000\366\366\365\000"
  "\366\366\365\000\366\366\365\000\366\366\365\000\366\366\365\000\000\000\000\010\000\000\000\020"
  "\000\000\000\024\000\000\000A\000\000\000\216\000\000\000\260\000\000\000\301\000\000\000\354\377\377\377\377"
  "\304\304\305\377\377\377\377\377\000\000\000\354\000\000\000\303\000\000\000\262\000\000\000\216"
  "\000\000\000A\000\000\000\024\000\000\000\024\000\000\000\010\366\366\365\000\366\366\365\000\366\366\365"
  "\000\366\366\365\000\366\366\365\000\366\366\365\000\366\366\365\000\366\366\365\000"
  "\366\366\365\000\366\366\365\000\366\366\365\000\366\366\365\000\366\366\365\000\366"
  "\366\365\000\000\000\000\020\000\000\000n\377\377\377\377\377\377\377\377\377\377\377\377"
  "\377\377\377\377\377\377\377\377\317\317\316\377\377\377\377\377\377\377"
  "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\000\000\000n\000\000\000\020"
  "\366\366\365\000\366\366\365\000\366\366\365\000\366\366\365\000\366\366\365\000\366"
  "\366\365\000\366\366\365\000\366\366\365\000\366\366\365\000\366\366\365\000\366\366"
  "\365\000\366\366\365\000\366\366\365\000\366\366\365\000\366\366\365\000\366\366\365"
  "\000\000\000\000\010\000\000\000J\000\000\000\304\377\377\377\377\330\330\330\377\330\330\330"
  "\377\330\331\330\377\330\330\330\377\330\330\331\377\330\331\330\377\330"
  "\330\330\377\377\377\377\377\000\000\000\304\000\000\000J\000\000\000\014\366\366\365\000\366"
  "\366\365\000\366\366\365\000\366\366\365\000\366\366\365\000\366\366\365\000\366\366"
  "\365\000\366\366\365\000\366\366\365\000\366\366\365\000\366\366\365\000\366\366\365"
  "\000\366\366\365\000\366\366\365\000\366\366\365\000\366\366\365\000\366\366\365\000"
  "\000\000\000\024\000\000\000_\000\000\000\316\377\377\377\377\342\342\342\377\342\342\342\377"
  "\342\342\342\377\341\341\342\377\342\342\342\377\377\377\377\377\000\000\000\317"
  "\000\000\000_\000\000\000\024\366\366\365\000\366\366\365\000\366\366\365\000\366\366\365\000"
  "\366\366\365\000\366\366\365\000\366\366\365\000\366\366\365\000\366\366\365\000\366"
  "\366\365\000\366\366\365\000\366\366\365\000\366\366\365\000\366\366\365\000\366\366"
  "\365\000\366\366\365\000\366\366\365\000\366\366\365\000\366\366\365\000\000\000\000\024\000"
  "\000\000_\000\000\000\317\377\377\377\377\354\353\353\377\354\354\354\377\353\353\354"
  "\377\377\377\377\377\000\000\000\320\000\000\000b\000\000\000\024\366\366\365\000\366\366\365"
  "\000\366\366\365\000\366\366\365\000\366\366\365\000\366\366\365\000\366\366\365\000"
  "\366\366\365\000\366\366\365\000\366\366\365\000\366\366\365\000\366\366\365\000\366"
  "\366\365\000\366\366\365\000\366\366\365\000\366\366\365\000\366\366\365\000\366\366"
  "\365\000\366\366\365\000\366\366\365\000\366\366\365\000\000\000\000\024\000\000\000_\000\000\000\317"
  "\377\377\377\377\366\366\365\377\377\377\377\377\000\000\000\320\000\000\000b\000\000\000\024"
  "\366\366\365\000\366\366\365\000\366\366\365\000\366\366\365\000\366\366\365\000\366"
  "\366\365\000\366\366\365\000\366\366\365\000\366\366\365\000\366\366\365\000\366\366"
  "\365\000\366\366\365\000\366\366\365\000\366\366\365\000\366\366\365\000\366\366\365"
  "\000\366\366\365\000\366\366\365\000\366\366\365\000\366\366\365\000\366\366\365\000"
  "\366\366\365\000\366\366\365\000\000\000\000\024\000\000\000_\000\000\000\307\377\377\377\377\000"
  "\000\000\307\000\000\000_\000\000\000\024\366\366\365\000\366\366\365\000\366\366\365\000\366\366"
  "\365\000\366\366\365\000\366\366\365\000\366\366\365\000\366\366\365\000\366\366\365"
  "\000\366\366\365\000\366\366\365\000\366\366\365\000\366\366\365\000\366\366\365\000"
  "\366\366\365\000\366\366\365\000\366\366\365\000\366\366\365\000\366\366\365\000\366"
  "\366\365\000\366\366\365\000\366\366\365\000\366\366\365\000\366\366\365\000\366\366"
  "\365\000\000\000\000\024\000\000\000M\000\000\000t\000\000\000M\000\000\000\024\366\366\365\000\366\366\365\000"
  "\366\366\365\000\366\366\365\000\366\366\365\000\366\366\365\000\366\366\365\000\366"
  "\366\365\000\366\366\365\000\366\366\365\000\366\366\365\000\366\366\365\000\366\366"
  "\365\000\366\366\365\000\366\366\365\000\366\366\365\000\366\366\365\000\366\366\365"
  "\000\366\366\365\000\366\366\365\000\366\366\365\000\366\366\365\000\366\366\365\000"
  "\366\366\365\000\366\366\365\000\366\366\365\000\366\366\365\000\000\000\000\010\000\000\000\020"
  "\000\000\000\010\366\366\365\000\366\366\365\000\366\366\365\000\366\366\365\000\366\366"
  "\365\000\366\366\365\000\366\366\365\000\366\366\365\000\366\366\365\000\366\366\365"
  "\000\366\366\365\000\366\366\365\000\366\366\365\000\366\366\365\000",
};
