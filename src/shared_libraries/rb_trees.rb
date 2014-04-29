# -*- coding: utf-8 -*-
# 
# Author: José Emiliano Cabrera Blancas (jemiliano.cabrera@gmail.com)
#
require 'ffi'

require File.expand_path(File.join(File.dirname(__FILE__),"double_linked_list"))


#
# Modulo para mapear los rb-tree de C a Ruby, junto con sus funciones.
#
module RBTree
  extend FFI::Library
  ffi_lib "lib/librb_tree.so"

  Item_type = enum( :point, 1,
                    :half_edge,
                    :face)

  class Tree < FFI::Struct
    layout :root, :pointer,
           :sentinel, :pointer,
           :size, :int,
           :type, Item_type,
           :min, :pointer,
           :max, :pointer  
  end

  attach_function :init_rb_tree, [Item_type], Tree.by_ref
  attach_function :destroy_rb_tree, [Tree.by_ref], :void

  attach_function :rb_insert, [Tree.by_ref, :pointer], :void
  attach_function :rb_search, [Tree.by_ref, :pointer], :pointer
  attach_function :rb_delete, [Tree.by_ref, :pointer], :pointer
  
  attach_function :rb_min, [Tree.by_ref], :pointer
  attach_function :rb_max, [Tree.by_ref], :pointer
  
  attach_function :rb_tree_to_list, [Tree.by_ref], List::List.by_ref

end

