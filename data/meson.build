subdir('card-style')
subdir('table')
i18n = import('i18n')


i18n.merge_file(
  input: 'games-card.desktop.in',
  output: 'games-card.desktop',
  install: true,
  po_dir: join_paths(meson.source_root(), 'po'),
  install_dir : join_paths(get_option('prefix'), 'share/applications'),
  type: 'desktop',
)
