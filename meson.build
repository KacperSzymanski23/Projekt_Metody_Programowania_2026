project(
  'Projekt_Metody_2026',
  'cpp',
  version: '0.0.1',
  meson_version: '>=1.1',
  default_options: 'cpp_std=c++20',
)

common_args = []

tracy_dep = dependency('tracy')

if get_option('tracy_enable')
  common_args += ['-DTRACY_ENABLE', '-DTRACY_NO_EXIT']
endif

subdir('src')

if get_option('tests')
  catch2_dep = dependency('catch2-with-main', default_options: ['tests=false'])

  if catch2_dep.found()
    subdir('tests')
  else
    message('Catch2 not found - skipping tests')
  endif
endif