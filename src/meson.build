gnome = import('gnome')

resources = gnome.compile_resources(
  'games-resources',
  join_paths(
    'resources', 'games-admin.gresource.xml'
  ),
  source_dir: 'resources',
  c_name: 'games_card',
  extra_args: '--generate-source'
)


sources = [
'main.c',
'games-utils.c',
'games-window.c',
 resources,
]

executable('games-card',
  sources : sources,
  dependencies : [gtk_deps],
  include_directories: top_srcdir,
  install : true,
  install_dir : get_option('bindir')
  )
