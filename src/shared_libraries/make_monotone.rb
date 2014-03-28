# -*- coding: utf-8 -*-
# 
# Author: José Emiliano Cabrera Blancas (jemiliano.cabrera@gmail.com)
#
require 'ffi'

require File.expand_path(File.join(File.dirname(__FILE__),"points"))
require File.expand_path(File.join(File.dirname(__FILE__),"half_edge"))
require File.expand_path(File.join(File.dirname(__FILE__),"face"))

require File.expand_path(File.join(File.dirname(__FILE__),"double_linked_list"))
require File.expand_path(File.join(File.dirname(__FILE__), "rb_trees"))
require File.expand_path(File.join(File.dirname(__FILE__), "dcel"))


#
# Modulo para mapear las funciones del encabezado make_monotone.h
#
module Monotone
  extend FFI::Library
  ffi_lib "lib/libmake_monotone.so"
  
  attach_function :make_monotone, [DCEL::DCEL.by_ref], :void

  Vertex_type = enum( :start, 1,
                      :split,
                      :end,
                      :merge,
                      :regular )

  attach_function :calculate_vertex_type, [Points::Point.by_ref], Vertex_type
end

