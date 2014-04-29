# -*- coding: utf-8 -*-
#!/usr/bin/env ruby

#
# Author: José Emiliano Cabrera Blancas (jemiliano.cabrera@gmail.com)
#

# Acciones permitidas:
#
#    compile: Compila para su uso con ruby-processing
#    compile_c: Compila para poder usar y probar tus funciones en ./main
#    test: Ejecuta las pruebas(si no esta compilado, seguramente truena esta accion)
#    clean: Borra todos los archivos que se generaron en la instalación

# Variables generales para compile y compile_c
# Compilador que se usa
@cc = "gcc"

# Aqui debes agregar los demás objectos que programes ejemplo : [ ..., "algorithms/heap.o"  ,...]
@objs = ["double_linked_list/double_linked_list.o","points/2d_points.o","half_edge/half_edge.o", "face/face.o"] +
  ["red_black_tree/rb_tree.o","dcel/dcel.o", "example.o", "algorithms/make_monotone.o"]

@cflags = "-I."
@debug = "-g"
@main = "main.o"

#Variables de compile
@shared = @objs.map {|obj| "#{obj[0...-1]}so"}

@lib_dir = "lib/"

# Detecta que sistema operativo utilizas, solo soporta: 
#          - MACOSX
#          - Linux

host_os = RbConfig::CONFIG['host_os']

if not((/linux/ =~ host_os).nil?)
  @so = "linux"
elsif not((/darwin/ =~ host_os).nil?)
  @so = "mac"
else
  puts "Sistema operativo no soportado"
  exit(0)
end

# Comprueba que las acciones que se le pidieron sean soportadas.
args = ARGV.clone
actions = ["compile","compile_c", "test", "clean"]
if (not(args.any?) or args.keep_if{|x| not(actions.include?(x))}.any?) then
  puts "Actions avaliable:"
  puts actions.map{|x| "\t"+x}
  exit(0)
end

# Compila todo en el ejecutable ./main de tal forma que tu puedas probar
# funcionalidades exclusivas de C antes de pasar a los tests.
def compile_c
  puts "Compilando archivos fuentes:"
  objs = @objs + [@main]
  objs.each do |obj|
    command = "#{@cc} #{@debug} -c -o #{obj} #{obj[0..-2] + "c"} #{@cflags}"
    puts "\t"+ command
    exit (0) if not((system(command)))
  end
  command = "#{@cc} #{@debug} -o #{@main[0..-3]} #{objs.join(" ")} #{@cflags}"
  puts "\t"+ command
  puts "No compilo de forma correcta" if not(system(command))
end	

# Compila el codigo de tal forma que se puedan usar las librerias en Ruby-Processing y
# los tests
def compile
  puts "Compilando archivos fuentes:"
  @objs.each do |obj|
    command = "#{@cc} -fpic -c -o #{obj} #{obj[0..-2] + "c"} #{@cflags}"
    puts "\t"+ command
    exit (0) if not((system(command)))
  end
  
  puts "Convirtiendo a bibliotecas dinamicas"
  system("mkdir lib")
  @shared.each do |obj|
    library = obj.split('/').last
    compiled_libraries = `ls #{@lib_dir}`.split(" ")
    
    libs = compiled_libraries.inject("") {
      |string,lib|
      string += "-l#{lib[3...-3]} "
    }
    
    if (@so == "linux")
      command = "#{@cc} -shared -Wl,-soname,lib/lib#{library} -o lib/lib#{library} #{obj[0..-3] + "o"}" +
                " -L#{@lib_dir} #{libs}"
    elsif (@so == "mac")
      command = "#{@cc} -shared -o lib/lib#{library} #{obj[0..-3] + "o"}" +
                " -L#{@lib_dir} #{libs}" 
    end
    puts "\t" + command
    puts "No compilo de forma correcta" if not((system(command)))
  end
end

# Ejectua los tests de la correspondiente practica
def test
  require File.expand_path(File.join(File.dirname(__FILE__), "tests/tests"))
  Test.run
end

# Borra todos los archivos generados por compile y compile_c
def clean
  puts "Borramos los archivos *.o"
  
  command = "rm #{(@objs + [@main]).join(" ")}"
  puts "\t" + command
  system(command)

  puts "Borramos el ejecutable main"
  command = "rm #{@main[0..-3]}"
  puts "\t" + command
  system(command)

  puts "Borramos todos los archivos .so"
  
  command = "rm lib/*"
  puts "\t" + command
  system(command)
end


#
# Ejecutan todos los comandos que se le enviaron
#
ARGV.each do 
  |action|
  send(action)
end
