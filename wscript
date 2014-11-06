#! /usr/bin/env python
# encoding: utf-8

APPNAME = 'kodo-cpp'
VERSION = '0.1.0'


def recurse_helper(ctx, name):
    if not ctx.has_dependency_path(name):
        ctx.fatal('Load a tool to find %s as system dependency' % name)
    else:
        p = ctx.dependency_path(name)
        ctx.recurse([p])


def options(opt):

    import waflib.extras.wurf_dependency_bundle as bundle
    import waflib.extras.wurf_dependency_resolve as resolve

    bundle.add_dependency(opt, resolve.ResolveGitMajorVersion(
        name='waf-tools',
        git_repository='github.com/steinwurf/waf-tools.git',
        major_version=2))

    bundle.add_dependency(opt, resolve.ResolveGitMajorVersion(
        name='boost',
        git_repository='github.com/steinwurf/boost.git',
        major_version=1))

    bundle.add_dependency(opt, resolve.ResolveGitMajorVersion(
        name='fifi',
        git_repository='github.com/steinwurf/fifi.git',
        major_version=14))

    bundle.add_dependency(opt, resolve.ResolveGitMajorVersion(
        name='gtest',
        git_repository='github.com/steinwurf/gtest.git',
        major_version=2))

    bundle.add_dependency(opt, resolve.ResolveGitMajorVersion(
        name='kodo',
        git_repository='github.com/steinwurf/kodo.git',
        major_version=19))

    bundle.add_dependency(opt, resolve.ResolveGitMajorVersion(
        name='sak',
        git_repository='github.com/steinwurf/sak.git',
        major_version=12))

    bundle.add_dependency(opt, resolve.ResolveGitMajorVersion(
        name='platform',
        git_repository='github.com/steinwurf/platform.git',
        major_version=1))

    bundle.add_dependency(opt, resolve.ResolveGitMajorVersion(
        name='cpuid',
        git_repository='github.com/steinwurf/cpuid.git',
        major_version=3))

    opt.load('wurf_configure_output')
    opt.load('wurf_dependency_bundle')
    opt.load('wurf_standalone')
    opt.load('wurf_tools')


def configure(conf):

    if conf.is_toplevel():

        conf.load('wurf_dependency_bundle')
        conf.load('wurf_tools')

        conf.load_external_tool('install_path', 'wurf_install_path')
        conf.load_external_tool('mkspec', 'wurf_cxx_mkspec_tool')
        conf.load_external_tool('project_gen', 'wurf_project_generator')
        conf.load_external_tool('runners', 'wurf_runner')

        recurse_helper(conf, 'boost')
        recurse_helper(conf, 'fifi')
        recurse_helper(conf, 'gtest')
        recurse_helper(conf, 'kodo')
        recurse_helper(conf, 'sak')
        recurse_helper(conf, 'platform')
        recurse_helper(conf, 'cpuid')

#        conf.recurse('examples/sample_makefile')


def build(bld):

    # The -fPIC is required for all underlying static libraries that will be
    # included in the shared library
    CXX = bld.env.get_flat("CXX")
    # Matches both /usr/bin/g++ and /usr/bin/clang++
    if 'g++' in CXX or 'clang' in CXX:
        bld.env.append_value('CXXFLAGS', '-fPIC')

    if bld.is_toplevel():

        bld.load('wurf_dependency_bundle')

        recurse_helper(bld, 'boost')
        recurse_helper(bld, 'fifi')
        recurse_helper(bld, 'gtest')
        recurse_helper(bld, 'kodo')
        recurse_helper(bld, 'sak')
        recurse_helper(bld, 'platform')
        recurse_helper(bld, 'cpuid')

        # Only build test when executed from the
        # top-level wscript i.e. not when included as a dependency
        # in a recurse call

        bld.recurse('test')
        bld.recurse('examples/encode_decode_simple')
        bld.recurse('examples/encode_decode_on_the_fly')
        # bld.recurse('examples/sample_makefile')
        bld.recurse('examples/sliding_window')
        bld.recurse('examples/switch_systematic_on_off')
        # bld.recurse('examples/udp_sender_receiver')
        bld.recurse('examples/use_trace_layers')


    # Build the shared library in the build root folder (we also place the
    # generated program binaries in this folder so that they can find the
    # shared library)
    bld.shlib(
        features='cxx',
        source=bld.path.ant_glob('src/**/*.cpp'),
        target='kodocpp',
        name='kodocpp',
        defines=['BUILD_KODOCPP_DLL'],
        install_path=None,
        export_includes='src',
        use=['kodo_includes', 'boost_includes', 'fifi_includes',
             'sak_includes', 'platform_includes'])
