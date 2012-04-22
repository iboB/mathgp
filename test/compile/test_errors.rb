require 'trollop'
require 'test/unit'

tools = {
  'gcc' =>  'gcc -S -x c++ -std=c++0x %s',
  'msvc' => 'cl /Zs /TP %s'
}

tools_list = tools.keys.join(', ')

options = Trollop::options do
  banner 'MathGP compilation test tool. Version 1.0.0'  
  opt :tool, "Selects the compilation tool. Currently the supported tools are: #{tools_list}", 
    :short => 't', :type => String, :default => 'gcc'
end
Trollop::die :tool, "must be one of the following: #{tools_list}" if !tools[options[:tool]]
  
COMPILE = tools[options[:tool]]

class InlineFile
  GEN_SRC = <<DATA
#include "../../mathgp/mathgp.h"
using namespace mathgp;
void f()
{
#include "%s"
}
DATA
  def initialize(filename)
    #File.open(filename, 'r').read
    @src_file = filename + '.tmp'
    File.open(@src_file, 'w') { |f| f.write(GEN_SRC % filename) }
  end
  
  def to_s
    @src_file
  end
  
  def close
    File.delete(@src_file)
  end    
end


def compile(file)
  output = `#{COMPILE % file.to_s} 2>&1` # 2>&1 redirects stderr to stdout
  status = $?.exitstatus
  
  return status, output
end

def compile_status(file)
  s, o = compile(file)
  s
end

def assert_compile_error(file)
  assert_not_equal 0, compile_status(file)
end

def assert_no_compile_error(file)
  assert_equal 0, compile_status(file)
end

class TestCompilation < Test::Unit::TestCase
  def test_aaa_first #quick and dirty way of ensuring this will be first
    assert_no_compile_error 'noerror.cxx'
    assert_compile_error 'error.cxx'
    assert_no_compile_error 'noerror_mathgp.cxx'
    
    inl = InlineFile.new('noerror_inline.cxx')
    assert_no_compile_error(inl)
    inl.close
    
    inl = InlineFile.new('error_inline.cxx')
    assert_compile_error(inl)
    inl.close
  end
  
  def test_cpps
    Dir['*.cpp'].each do |file|
      assert_compile_error(file)
    end
  end
  
  def test_hs
    Dir['*.h'].each do |file|
      inl = InlineFile.new(file)
      assert_compile_error(inl)
      inl.close
    end
  end
end

