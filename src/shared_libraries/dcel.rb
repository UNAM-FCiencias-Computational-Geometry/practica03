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

#
# Modulo para mapear una DCEL y sus funciones de C a Ruby.
#
module DCEL
  extend FFI::Library
  ffi_lib "lib/libdcel.so"
  
  class DCEL < FFI::Struct
    layout :face, RBTree::Tree.by_ref,
           :vertex, RBTree::Tree.by_ref,
           :half_edge, RBTree::Tree.by_ref 
  end
  
  attach_function :incident_he_to_v, [Points::Point.by_ref], List::List.by_ref
  attach_function :incident_f_to_f, [Face::Face.by_ref], List::List.by_ref
  attach_function :incident_he_to_f, [Face::Face.by_ref], List::List.by_ref
end

#
# Modulo para mapear la funcion que crea el ejemplo de C a Ruby.
#
module ExampleDCEL
  extend FFI::Library
  
  ffi_lib "lib/libexample.so"
  
  attach_function :construct_example, [], DCEL::DCEL.by_ref
end
