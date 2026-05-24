test_inc = include_directories('.')

test_sources = [
    'test_board.cpp',
    'test_move.cpp',
    'test_strategies.cpp',
    'test_game.cpp',
]

foreach src : test_sources
    test_name = src.split('.')[0]
    exe = executable(
        test_name,
        src,
        include_directories: [tictactoe_inc, test_inc],
        link_with: library_tictactoe,
        dependencies: catch2_dep,
    )
    test(test_name, exe)
endforeach