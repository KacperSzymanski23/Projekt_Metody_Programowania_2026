project(
  'Projekt_Metody_2026',
  'cpp',
  version: '0.0.1',
  default_options: 'cpp_std=c++20',
)

if get_option('tests')
  catch2_dep = dependency('catch2')

  if catch2_dep.found()
    subdir('tests')
  else
    message('Catch2 not found - skipping tests')
  endif
endif

subdir('src')