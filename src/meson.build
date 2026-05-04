lib_src = files(
  'alphaBetaStrategy.cpp',
  'board.cpp',
  'boardExt.cpp',
  'minMaxStrategy.cpp',
  'move.cpp',
  'myexceptions.cpp',
  'strategy.cpp',
  'ticTacToeGame.cpp',
)

include = include_directories('.')

library_tictactoe = library('tictactoe', sources: lib_src, include_directories: include)

src = files('main.cpp')

app_exe = executable(
  meson.project_name(),
  sources: [src],
  link_with: [library_tictactoe],
)

test('general-test', app_exe, workdir: meson.project_build_root() + '/src/')