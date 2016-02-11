#! /usr/bin/env python
# encoding: utf-8

import os
import waflib.extras.wurf_options

APPNAME = 'kodo-cpp'
VERSION = '5.0.0'


def options(opt):

    opt.load('wurf_common_tools')


def resolve(ctx):

    import waflib.extras.wurf_dependency_resolve as resolve

    ctx.load('wurf_common_tools')

    ctx.add_dependency(resolve.ResolveVersion(
        name='waf-tools',
        git_repository='github.com/steinwurf/waf-tools.git',
        major=3))

    ctx.add_dependency(resolve.ResolveVersion(
        name='kodo-c',
        git_repository='github.com/steinwurf/kodo-c.git',
        major=8))

    # Internal dependencies
    if ctx.is_toplevel():

        ctx.add_dependency(resolve.ResolveVersion(
            name='gtest',
            git_repository='github.com/steinwurf/gtest.git',
            major=3))


def configure(conf):

    conf.load("wurf_common_tools")


def build(bld):

    bld.load("wurf_common_tools")

    bld.env.append_unique(
        'DEFINES_STEINWURF_VERSION',
        'STEINWURF_KODOCPP_VERSION="{}"'.format(VERSION))

    # Define the kodocpp includes that use the kodo-c shared library
    bld(name='kodocpp_includes',
        includes='src',
        export_includes='src',
        use=['kodoc'])

    # Define the kodocpp static includes that use the kodo-c static library
    bld(name='kodocpp_static_includes',
        includes='src',
        export_includes='src',
        use=['kodoc_static'])

    if bld.is_toplevel():

        # Only build test when executed from the
        # top-level wscript i.e. not when included as a dependency
        # in a recurse call
        bld.recurse('test')
        bld.recurse('examples/encode_decode_on_the_fly')
        bld.recurse('examples/encode_decode_simple')
        bld.recurse('examples/fulcrum')
        bld.recurse('examples/is_symbol_pivot_counter')
        bld.recurse('examples/perpetual')
        bld.recurse('examples/reed_solomon')
        bld.recurse('examples/sliding_window')
        bld.recurse('examples/sparse_seed')
        bld.recurse('examples/switch_systematic_on_off')
        bld.recurse('examples/tutorial')
        bld.recurse('examples/udp_sender_receiver')
        bld.recurse('examples/uncoded_symbols')
        bld.recurse('examples/use_trace_layers')

        # Install the kodocpp headers and kodoc.h to the 'include' folder
        if bld.has_tool_option('install_path'):
            install_path = bld.get_tool_option('install_path')
            install_path = os.path.abspath(os.path.expanduser(install_path))
            include_path = os.path.join(install_path, 'include')

            start_dir = bld.path.find_dir('src')
            bld.install_files(include_path, start_dir.ant_glob('**/*.hpp'),
                              cwd=start_dir, relative_trick=True)

            start_dir = os.path.join(bld.dependency_path('kodo-c'), 'src')
            start_dir = bld.root.find_dir(start_dir)
            bld.install_files(include_path, ['kodoc/kodoc.h'],
                              cwd=start_dir, relative_trick=True)
