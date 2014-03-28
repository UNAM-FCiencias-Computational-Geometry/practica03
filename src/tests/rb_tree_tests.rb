# -*- coding: utf-8 -*-
# 
# Author: José Emiliano Cabrera Blancas (jemiliano.cabrera@gmail.com)
#

require File.expand_path(File.join(File.dirname(__FILE__), "../shared_libraries/rb_trees"))

#
# Reabre el modulo de Test para agregar las clases TestRBTree, la cual
# tiene los test de las funciones de la estructura de C.
#
module Test
  
  class TestRBTree

    # Public: Prueba la funcion min en un arbol vacio
    #
    # Examples
    #
    #     Test::TestRBTree.min_on_empty_tree
    #     # => true
    # 
    # Regresa true si la funcion en C responde de forma correcta o false en caso 
    # contrario.
    def self.min_on_empty_tree
      tree = RBTree.init_rb_tree(:point)
      result = RBTree.rb_min(tree).null?
      RBTree.destroy_rb_tree(tree)

      result
    end

    # Public: Prueba la funcion max en un arbol vacio
    #
    # Examples
    #
    #     Test::TestRBTree.max_on_empty_tree
    #     # => true
    # 
    # Regresa true si la funcion en C responde de forma correcta o false en caso 
    # contrario.
    def self.max_on_empty_tree
      tree = RBTree.init_rb_tree(:point)
      result = RBTree.rb_max(tree).null?
      RBTree.destroy_rb_tree(tree)

      result
    end
    
    # Public: Prueba la funcion search en un arbol vacio
    #
    # Examples
    #
    #     Test::TestRBTree.search_on_empty_tree
    #     # => true
    # 
    # Regresa true si la funcion en C responde de forma correcta o false en caso 
    # contrario.
    def self.search_on_empty_tree
      tree = RBTree.init_rb_tree(:point)
      
      point = Points.init_point_empty
      
      result = RBTree.rb_search(tree,point).null?
      RBTree.destroy_rb_tree(tree)
      Points.destroy_point(point)

      result
    end
    
    # Public: Prueba la funcion delete en un arbol vacio
    #
    # Examples
    #
    #     Test::TestRBTree.delete_on_empty_tree
    #     # => true
    # 
    # Regresa true si la funcion en C responde de forma correcta o false en caso 
    # contrario.
    def self.delete_on_empty_tree
      tree = RBTree.init_rb_tree(:point)
      
      point = Points.init_point_empty
      
      result = RBTree.rb_delete(tree,point).null?
      RBTree.destroy_rb_tree(tree)
      Points.destroy_point(point)

      result
    end

    # Public: Prueba la funcion min en un arbol no vacio
    #
    # Examples
    #
    #     Test::TestRBTree.rb_min
    #     # => true
    # 
    # Regresa true si la funcion en C responde de forma correcta o false en caso 
    # contrario.
    def self.rb_min
      tree = RBTree.init_rb_tree(:point)
      raw_numbers = Array.new

      size = rand(1000) + 100

      size.times.each do |p|
        raw_numbers << rand(1000) 
      end
      
      raw_numbers.uniq!
      
      points = Array.new
      
      raw_numbers.each do |point|
        points << Points.init_point(point.to_f,0.to_f,"")
      end

      points.each do |point|
        RBTree.rb_insert(tree,point)
      end

      min = Points.cast_point(RBTree.rb_min(tree))
      
      raw_min = raw_numbers.sort!{|x,y| y<=>x}.first

      result = raw_min == min[:x]

      result
    end

    # Public: Prueba la funcion max en un arbol no vacio
    #
    # Examples
    #
    #     Test::TestRBTree.rb_max
    #     # => true
    # 
    # Regresa true si la funcion en C responde de forma correcta o false en caso 
    # contrario.
    def self.rb_max
      tree = RBTree.init_rb_tree(:point)
      raw_numbers = Array.new
      
      size = rand(1000) + 100
      
      size.times.each do |p|
        raw_numbers << rand(1000).to_f
      end
      
      raw_numbers.uniq!
      
      points = Array.new
      
      raw_numbers.each do |point|
        points << Points.init_point(point,0,"")
      end
      
      points.each do |point|
        RBTree.rb_insert(tree,point)
      end
      
      max = Points.cast_point(RBTree.rb_max(tree))
      
      raw_max = raw_numbers.sort{|x,y| x<=>y}.first

      result = raw_max == max[:x]
            
      result
    end
    
    # Public: Prueba la funcion search en un arbol no vacio
    #
    # Examples
    #
    #     Test::TestRBTree.rb_search
    #     # => true
    # 
    # Regresa true si la funcion en C responde de forma correcta o false en caso 
    # contrario.
    def self.rb_search
      tree = RBTree.init_rb_tree(:point)
      raw_numbers = Array.new
      
      size = rand(1000) + 100
      random_index = rand(size)
      
      raw_search = nil

      size.times.each do |p|
        rand_number = rand(1000)
        if (p == random_index) then
          raw_search = rand_number
        end
        raw_numbers << rand_number
      end
      
      raw_numbers.uniq!
      
      points = Array.new
      
      raw_numbers.each do |point|

        new_point =  Points.init_point(point,0,"")

        if (point == raw_search)
          raw_search = new_point
        end
        points << new_point
      end
      
      points.each do |point|
        RBTree.rb_insert(tree,point)
      end
      
      search = Points.cast_point(RBTree.rb_search(tree,raw_search))
      
      result = raw_search.pointer == search.pointer
      
      result
    end    
    
    # Public: Prueba la insercion y borrado de numeros positivos.
    #
    # Examples
    #
    #     Test::TestRBTree.insert_delete_positive_numbers
    #     # => true
    # 
    # Regresa true si la funcion en C responde de forma correcta o false en caso 
    # contrario.
    def self.insert_delete_positive_numbers
      tree = RBTree.init_rb_tree(:point)

      raw_numbers = Array.new

      size = rand(1000) + 100

      size.times.each do |p|
        rand_number = rand(1000).to_f
        raw_numbers << rand_number
      end

      raw_numbers.uniq!

      points = Array.new
      raw_numbers.each do |point|
        new_point = Points.init_point(point,0.to_f,"")
        points << new_point
      end

      raw_numbers.sort!{ |x,y| y<=>x }

      points.each do |point|
        RBTree.rb_insert(tree, point)
      end
      
      order_points = Array.new

      raw_numbers.size.times.each do
        point = Points.cast_point(RBTree.rb_min(tree))
        RBTree.rb_delete(tree,point)
        order_points << point[:x]
      end
      
      result = raw_numbers == order_points
      result 
    end

    
    # Public: Prueba la insercion y borrado de numeros negativos.
    #
    # Examples
    #
    #     Test::TestRBTree.insert_delete_negative_numbers
    #     # => true
    # 
    # Regresa true si la funcion en C responde de forma correcta o false en caso 
    # contrario.
    def self.insert_delete_negative_numbers
      tree = RBTree.init_rb_tree(:point)
      
      raw_numbers = Array.new

      size = rand(1000) + 100

      size.times.each do |p|
        rand_number = rand(1000)*-1
        raw_numbers << rand_number.to_f
      end

      raw_numbers.uniq!

      points = Array.new
      raw_numbers.each do |point|
        new_point = Points.init_point(point,0,"")
        points << new_point
      end

      raw_numbers.sort!{ |x,y| y<=>x }

      points.each do |point|
        RBTree.rb_insert(tree, point)
      end
      
      order_points = Array.new

      raw_numbers.size.times.each do
        point = Points.cast_point(RBTree.rb_min(tree))
        RBTree.rb_delete(tree,point)
        order_points << point[:x]
      end

      result = raw_numbers == order_points
      result 
    end
  
    
    # Public: Prueba la insercion y borrado de numeros repetidos.
    #
    # Examples
    #
    #     Test::TestRBTree.insert_delete_repeat_numbers
    #     # => true
    # 
    # Regresa true si la funcion en C responde de forma correcta o false en caso 
    # contrario.
    def self.insert_delete_repeat_numbers
      tree = RBTree.init_rb_tree(:point)
      
      raw_numbers = Array.new
      
      size = rand(1000) + 100
      
      size.times.each do |p|
        rand_number = rand(1000)
        raw_numbers << rand_number.to_f
      end
      
      points = Array.new
      raw_numbers.each do |point|
        new_point = Points.init_point(point,0,"")
        points << new_point
      end

      raw_numbers.sort!{ |x,y| y<=>x }
      
      points.each do |point|
        RBTree.rb_insert(tree, point)
      end
      
      order_points = Array.new
      
      raw_numbers.size.times.each do
        point = Points.cast_point(RBTree.rb_min(tree))
        point = Points.cast_point(RBTree.rb_delete(tree,point))
        order_points << point[:x]
      end

      points.each do |point|
        Points.destroy_point(point)
      end
      
      result = raw_numbers == order_points
      RBTree.destroy_rb_tree(tree)
      result 
    end
  end  
end
