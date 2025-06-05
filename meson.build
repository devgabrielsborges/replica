project('replica', 'c',
        version : '1.0.0',
        default_options : ['warning_level=3', 'c_std=c11'])

proj_name = meson.project_name()

# For development builds, use the source directory
# For installed builds, use the proper data directory
if get_option('buildtype') == 'debug' or get_option('buildtype') == 'debugoptimized'
    # Development build - use source directory
    datadir_abs = meson.current_source_dir()
else
    # Release/installed build - use proper data directory
    datadir_abs = get_option('prefix') / get_option('datadir') / proj_name
endif

c_args = ['-DREPLICA_DATADIR="@0@"'.format(datadir_abs)]

src = files(
  'src/main.c',
  'src/copy.c',
  'src/print_utils.c'
)

replica = executable('rpc', src,
                     c_args : c_args,
                     install : true)

test('test', replica)

github_install_parent_dir = get_option('datadir') / proj_name / '.github'

install_subdir(
  '.github/prompts',
  install_dir: github_install_parent_dir
)

install_subdir(
  '.github/instructions',
  install_dir: github_install_parent_dir
)
