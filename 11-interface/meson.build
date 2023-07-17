project('11-interface', 'c',
  version : '0.1',
  default_options : ['warning_level=3'])

gobject = dependency('gobject-2.0')

srcs = files('main.c',
  'tcomparable.c',
  'tint.c',
  'tdouble.c',
  'tnumber.c',
  'tstr.c')

executable('11-interface',
           srcs,
           dependencies : gobject,
           install : false)
