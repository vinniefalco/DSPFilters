
import os, sys
from waflib import Logs

def options(opt):
    opt.load('compiler_cxx')
    config_options = opt.get_option_group('configure options')
    config_options.add_option('--build-demo',
        action='store_true',
        dest='build_demo',
        help='build the demo application [default: false]')

def configure(conf):
    conf.load('compiler_cxx')
    configure_lib(conf)
    if conf.options.build_demo:
        Logs.warn('DSPFiltersDemo: demo application will also be built.')
        configure_demo(conf)

def configure_lib(conf):
    pass

def configure_demo(conf):
    conf.env['BUILD_DEMO'] = True
    configure_juce(conf)

def configure_juce(conf):
    juce_required_libs=[]
    juce_required_packages=[]
    
    if os.name.startswith('posix') and not sys.platform.startswith('darwin'):
        juce_required_libs+=['dl', 'pthread', 'rt']
        juce_required_packages+=['freetype2', 'gl', 'glu', 'x11', 'xinerama', 'alsa', 'xext']
    else:
        # TODO: add Darwin and non-POSIX dependency checks
        conf.fatal('DSPFiltersDemo: Building DSPFiltersDemo with waf is currently only possible on'
            ' POSIX systems with X11.')

    for l in juce_required_libs:
        conf.check(
            lib=l,
            uselib_store=l)
    for pkg in juce_required_packages:
        conf.check_cfg(
            package=pkg,
            uselib_store=pkg,
            args=['--cflags', '--libs'])
    conf.env.append_value('JUCE_USELIBS', juce_required_libs)
    conf.env.append_value('JUCE_USELIBS', juce_required_packages)


def build(bld):
    build_lib(bld)
    if bld.env['BUILD_DEMO']:
        build_demo(bld)

def build_lib(bld):
    dspfilters_include_dir = bld.path.find_dir('shared/DSPFilters/include')
    bld.install_files('${PREFIX}/include',
        dspfilters_include_dir.ant_glob('**/*.h'),
        cwd=dspfilters_include_dir,
        relative_trick=True)
    bld.shlib(
        source=bld.path.ant_glob('shared/DSPFilters/source/*.cpp'),
        includes='shared/DSPFilters/include',
        target='DSPFilters')

def build_demo(bld):
    build_juce(bld)
    bld.program(
        source=bld.path.ant_glob('shared/DSPFiltersDemo/source/*.cpp'),
        includes=['shared/DSPFiltersDemo/source', 'shared/DSPFilters/include', 'shared/JuceAmalgam'],
        use=bld.env['JUCE_USELIBS'] + ['JuceAmalgam', 'DSPFilters'],
        target='DSPFiltersDemo')

def build_juce(bld):
    bld.stlib(
        source=bld.path.ant_glob('shared/JuceAmalgam/*.cpp'),
        includes='shared/JuceAmalgam',
        use=bld.env['JUCE_USELIBS'],
        target='JuceAmalgam')

# vim: syntax=python
