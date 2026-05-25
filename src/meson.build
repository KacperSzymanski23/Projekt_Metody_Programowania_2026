lib_src = files(
  'lib/alphaBetaStrategy.cpp',
  'lib/board.cpp',
  'lib/minMaxStrategy.cpp',
  'lib/move.cpp',
  'lib/ticTacToeGame.cpp',
)

tictactoe_inc = include_directories('lib')

library_tictactoe = library('tictactoe', sources: lib_src, include_directories: tictactoe_inc)

tictactoe_dep = declare_dependency(link_with: library_tictactoe, include_directories: tictactoe_inc)

src = files('main.cpp')

app_exe = executable(
  meson.project_name(),
  sources: [src],
  dependencies: [tictactoe_dep],
)

test('general-test', app_exe, workdir: meson.project_build_root() + '/src/')