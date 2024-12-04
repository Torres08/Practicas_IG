
##############################################################
#  Practicas de Informática Gráfica. Curso 2022/2023.
#  Makefile actualizado para la organización en carpetas.
##############################################################

# EJECUTABLE= Nombre del fichero ejecutable que queremos crear

EJECUTABLE = bin/practicasIG

# Directorios
SRCDIR = src
INCDIR = include
OBJDIR = build

# Archivos fuente y sus correspondientes archivos objeto
MODULOS = $(OBJDIR)/practicasIG.o $(OBJDIR)/entradaTeclado.o $(OBJDIR)/visual.o \
          $(OBJDIR)/mouse.o $(OBJDIR)/modelo.o $(OBJDIR)/file_ply_stl.o $(OBJDIR)/Ejes.o $(OBJDIR)/Escena.o $(OBJDIR)/MiMalla.o $(OBJDIR)/boton.o

# Inclusión de directorios
INCLUDEDIR = /usr/X11R6/include
CFLAGS = -g -c -DXWINDOWS -I$(INCLUDEDIR) -I./$(INCDIR)

# Librerías
LIBSDIR = /usr/X11R6/lib
LDFLAGS = -L$(LIBSDIR)
LIBS = -lglut -lGLU -lGL -lX11 -lXext -lc -lm -ljpeg

# Compilador
CC = g++

################### NO MODIFICAR A PARTIR DE AQUÍ #####################

# Regla para construir el ejecutable
$(EJECUTABLE): $(MODULOS)
	mkdir -p bin
	$(CC) -o $(EJECUTABLE) $(MODULOS) $(LDFLAGS) $(LIBS)

# Regla genérica para compilar .c y .cc en .o
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) $< -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.cc
	mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) $< -o $@

# Limpieza de archivos objeto y ejecutable
clean:
	rm -rf $(OBJDIR) $(EJECUTABLE)

# Regla para ejecutar el programa
ejecutar: $(EJECUTABLE)
	./$(EJECUTABLE)

# Regla para hacer limpieza y ejecutar
total: clean ejecutar


.PHONY: clean




