# Copyright © 2017-2018 Intel Corporation

# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:

# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.

# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.


gen_builder_hpp = custom_target(
  'gen_builder.hpp',
  input : [
    swr_gen_llvm_ir_macros_py,
    join_paths(
      dep_llvm.get_configtool_variable('includedir'), 'llvm', 'IR',
      'IRBuilder.h'
    )
  ],
  output : 'gen_builder.hpp',
  command : [
    prog_python2, '@INPUT0@', '--input', '@INPUT1@', '--output', '@OUTPUT@',
    '--gen_h', '--output-dir', '@OUTDIR@'
  ],
  depend_files : swr_gen_builder_depends,
  build_by_default : true,
)

gen_builder_x86_hpp = custom_target(
  'gen_builder_x86.hpp',
  input : '../codegen/gen_llvm_ir_macros.py',
  output : 'gen_builder_x86.hpp',
  command : [
    prog_python2, '@INPUT0@', '--gen_x86_h', '--output', '@OUTPUT@',
    '--output-dir', '@OUTDIR@'
  ],
  depend_files : swr_gen_builder_depends,
)

