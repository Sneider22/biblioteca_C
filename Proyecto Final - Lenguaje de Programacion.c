// Programa para la Administracion de una Biblioteca
// Se añaden los ficheros de inclusión necesarios para el correcto funcionamiento del programa
#include <stdio.h>
#include <stdlib.h>

//Se utiliza una estructura que almacene los datos de disponiblidad
typedef struct disponible
{
  int cantidad;
} disponible;

//Se utiliza una estructura que almacene los datos del prestamo
typedef struct prestado
{
  int lector;
  int dia;
  int mes;
  int ano;
} prestado;

//Se utiliza una estructura que almacene los datos de cada usuario (numero, nombre, apellido y direccion)
//Dentro de la estructura se utiliza una union con los miembros disponible y prestado
typedef struct usuario
{
  int num;
  char nombre[20];
  int estado;
  char apellido[20];
  char direccion[20];
  union
  {
    disponible disp;
    prestado pres;
  };
} usuario;


//Se utiliza una estructura que almacene los datos de cada libro (numero, titulo, autor y condicion)
//Dentro de la estructura se utiliza una union con los miembros disponible y prestado
typedef struct libro
{
  int num;
  char titulo[50];
  int estado;
  char autor[30];
  char condiciones[10];
  union
  {
    disponible disp;
    prestado pres;
  };
} libro;

//Se agrega un fichero con apuntador *bib que almacena los datos guardados en la estructura libro bajo el nombre lib
FILE *bib;
libro lib;
//Se agrega un fichero con apuntador *use que almacena los datos guardados en la estructura usuario bajo el nombre user
FILE *use;
usuario user;

//Se trabaja el cuerpo del menu con una variable de tipo char
char opcion_menu()
{
  system("cls");
  printf("\n");
//Se imprime en pantalla la informacion de la biblioteca
  printf("     *  *  *  *  *  *  *  *  *        Bienvenido a la Biblioteca Los Galpones        *  *  *  *  *  *  *  *  *  *\n\n");
  printf("     DIRECCION: 29-11 Transversal 8, Caracas 1071, Miranda\n");
  printf("     HORARIO: Martes a Viernes: 11AM - 7PM - Sabados: 11AM - 4PM\n\n");
  printf("     El sistema de control de la Biblioteca Los Galpones cuenta con una serie de funciones...\n");
  printf("     Funciones especializadas en el control de registro de libros y usuarios, asi como un listado de: \n");
  printf("     Los libros disponibles, los clientes mas frecuentes y tambien un sistema de prestamo con fechas de devolucion.\n");
  printf("\n");



//Se imprime en pantalla las opciones del sistema
  printf("     *** Opciones ***\n\n");
  printf("        (U)suario - Registro\n");
  printf("        (M)ostrar Registro de Usuarios\n");
  printf("        (A)ctualizar Registro de Libros\n");
  printf("        (L)istar Registro de Libros\n");
  printf("        (P)restar Libro\n");
  printf("        (R)ecibir Libro\n");
  printf("        (F)in\n");
  printf("        > ");
  return (toupper(getche()));
}

//Se trabaja el proceso de encontrar usuarios con estructuras iterativas dentro de una variable de tipo entero
int encontrar_usuario(int n)
{
  fread(&user,sizeof(usuario),1,use);
  while (!feof(use))
  {
    if (user.num == n)
    {
      fseek(use,-sizeof(usuario),SEEK_CUR);
      return 1;
    }
    fread(&user,sizeof(usuario),1,use);
  }
  return 0;
}

//Se trabaja el proceso de encontrar libros con estructuras iterativas dentro de una variable de tipo entero
int encontrar_libro(int n)
{
  fread(&lib,sizeof(libro),1,bib);
  while (!feof(bib))
  {
    if (lib.num == n)
    {
      fseek(bib,-sizeof(libro),SEEK_CUR);
      return 1;
    }
    fread(&lib,sizeof(libro),1,bib);
  }
  return 0;
}

//Se declara una funcion de retorno nulo (void) para el registro de usuarios
void usuario_registro()
{
  int num;
  //Apertura de archivo para guardar los datos de los usuarios
  use = fopen("clientes.dat","a+b");
  if (use == NULL)
  {
    printf("\nError al abrir el archivo\n");
    return;
  }
  printf("\n");
  printf("Numero del Usuario: ");
  scanf("%d",&num);
  if (encontrar_usuario(num) == 1)
    printf("Ya existe un usuario registrado con ese numero!\n");
  else
  {
    user.num = num;
    printf("Nombre del Usuario: ");
    fflush(stdin);
    gets(user.nombre);
    user.estado = 0;
    user.disp.cantidad = 0;
    printf("Apellido del Usuario: ");
     fflush(stdin);
    gets(user.apellido);
    printf("Direccion del Usuario: ");
     fflush(stdin);
    gets(user.direccion);
    fwrite(&user,sizeof(usuario),1,use);
    printf("Usuario %d incorporado al registro.\n",num);
  }
  fclose(use);
}


//Se declara una funcion de retorno nulo (void) para mostrar el listado de usuarios previamente registrados
void usuario_listado()
{
  //Se define un maximo de lineas mostradas por pantalla
  #define MAX_LINEAS 5
  int lin,pag;
  //Apertura de archivo para mostrar los datos de los usuarios
  use = fopen("clientes.dat","r+b");
  if (use == NULL)
  {
    printf("\nError al abrir el archivo\n");
    return;
  }
  pag = 0;
  lin = MAX_LINEAS;
  fread(&user,sizeof(usuario),1,use);
  while (!feof(use))
  {
    if (lin == MAX_LINEAS)
    {
      lin = 0;
      pag++;

      //Se imprime por pantalla el listado de los usuarios registrados
      system("Cls");
      printf("       LISTADO DEL REGISTRO Biblioteca Los Galpones %24s Pag. %03d\n"," ",pag);
      printf("       +-------+-----------------+------------------+-------------------+\n");
      printf("       |  NUM  | Nombre          | Apellido         | Direccion         |\n");
      printf("       +-------+-----------------+------------------+-------------------+\n\n\n");
    }
    lin++;
    printf(" %05d | %23s | %16s | %17s |",user.num,user.nombre,user.apellido,user.direccion);
    (lib.estado == 0);
    printf("\n");
  fread(&user,sizeof(usuario),1,use);
    if (feof(use) || (lin == MAX_LINEAS))
    {
      if (!feof(use))
        system("Pause");
    }
  }
  fclose(use);
}

//Se declara una funcion de retorno nulo (void) para el registro de libros
void actualizar_registro()
{
  int num;
  //Apertura de archivo para guardar los datos de los libros
  bib = fopen("libros.dat","a+b");
  if (bib == NULL)
  {
    printf("\nError al abrir el archivo\n");
    return;
  }
  printf("\n");
  printf("Numero del libro: ");
  scanf("%d",&num);
  if (encontrar_libro(num) == 1)
    printf("Ya existe un libro registrado con ese numero!\n");
  else
  {
    lib.num = num;
    printf("Titulo del libro: ");
    fflush(stdin);
    gets(lib.titulo);
    lib.estado = 0;
    lib.disp.cantidad = 0;
    printf("Autor del Libro: ");
     fflush(stdin);
    gets(lib.autor);
    printf("Condicion del Libro: ");
     fflush(stdin);
    gets(lib.condiciones);
    fwrite(&lib,sizeof(libro),1,bib);
    printf("Libro %d incorporado al registro.\n",num);
  }
  fclose(bib);
}



//Se declara una funcion de retorno nulo (void) para mostrar el listado de libros previamente registrados
void listar_registro()
{
  //Maximo de lineas mostradas por pantalla
  #define MAX_LINEAS 5
  int lin,pag;
  //Apertura de archivo para mostrar los datos de los libros
  bib = fopen("libros.dat","r+b");
  if (bib == NULL)
  {
    printf("\nError al abrir el archivo\n");
    return;
  }
  pag = 0;
  lin = MAX_LINEAS;
  fread(&lib,sizeof(libro),1,bib);
  while (!feof(bib))
  {
    if (lin == MAX_LINEAS)
    {
      lin = 0;
      pag++;
      //Se imprime por pantalla el listado de los libros registrados
      system("Cls");
      printf("       LISTADO DEL REGISTRO Biblioteca Los Galpones %24s Pag. %03d\n"," ",pag);
      printf("       +-------+-------------------+----------------------+-----------------+-------+--------------+\n");
      printf("       |  NUM  | Titulo            | Autor                | Condicion       |  STT  |  INFORMACION |\n");
      printf("       +-------+-------------------+----------------------+-----------------+-------+--------------+\n\n\n");
    }
    lin++;
    printf(" %05d | %25s | %20s | %15s |",lib.num,lib.titulo,lib.autor,lib.condiciones);
    if (lib.estado == 0)
      printf("  D | P:%04d       \n",lib.disp.cantidad);
    else
      printf("  P | D:%02d/%02d/%04d \n",
             lib.pres.dia,lib.pres.mes,lib.pres.ano);
    fread(&lib,sizeof(libro),1,bib);
    if (feof(bib) || (lin == MAX_LINEAS))
    {
      if (!feof(bib))
        system("Pause");
    }
  }
  fclose(bib);
}

//Se declara una funcion de retorno nulo (void) para manejar el proceso de prestamos de los libros
void prestamo()
{
  int num;
  //Apertura de archivo para trabajar los datos de los libros
  bib = fopen("libros.dat","r+b");
  if (bib == NULL)
  {
    printf("\nError al abrir el archivo\n");
    return;
  }
  printf("\n");
  printf("Numero del libro ..... ");
  scanf("%d",&num);
  if (encontrar_libro(num) == NULL)
    printf("Este libro no esta registrado!\n");
  else
  {
    fread(&lib,sizeof(libro),1,bib);
    if (lib.estado == 1)
      printf("Este libro ya ha sido prestado (Devolucion el %02d/%02d/%04d)\n",
             lib.pres.dia,lib.pres.mes,lib.pres.ano);
    else
    {
      lib.estado = 1;
      lib.pres.lector = lib.disp.cantidad+1;
      printf("Fecha de devolucion ... ");
      scanf("%d/%d/%d",&lib.pres.dia,&lib.pres.mes,&lib.pres.ano);
      fseek(bib,-sizeof(libro),SEEK_CUR);
      fwrite(&lib,sizeof(libro),1,bib);
      //El proceso finalizo, se imprime por pantalla "prestamo listo"
      printf("Prestamo listo!\n");
    }
  }
  fclose(bib);
}
//Se declara una funcion de retorno nulo (void) para manejar el proceso de devolucion de los libros
void recibir()
{
  int num;
  //Apertura de archivo para trabajar los datos de los libros
  bib = fopen("libros.dat","r+b");
  if (bib == NULL)
  {
    printf("\nError al abrir el archivo\n");
    return;
  }
  printf("\n");
  printf("Numero del libro ..... ");
  scanf("%d",&num);
  if (encontrar_libro(num) == 0)
    printf("Este libro no esta registrado!\n");
  else
  {
    fread(&lib,sizeof(libro),1,bib);
    if (lib.estado == 0)
      printf("Este libro ya esta disponible.\n");
    else
    {
      lib.estado = 0;
      lib.disp.cantidad = lib.pres.lector;
      fseek(bib,-sizeof(libro),SEEK_CUR);
      fwrite(&lib,sizeof(libro),1,bib);
      //El proceso finalizo, se imprime por pantalla "devolucion lista"
      printf("Devolucion lista!\n");
    }
  }
  fclose(bib);
}

//Se declara la funcion main, se muestran las diferentes funciones void que forman el cuerpo principal
int main(int args, char * arg[])
{
  //Se modifica la estetica del programa con un system color
  //Letra F (Fondo blanco brillante)
  //Numero 0 (Letras negras)
  system("COLOR F0");
  //Se trabaja el cuerpo del menu con una variable de tipo char
  char op;

  do
  {
    op = opcion_menu();
    //Se anida una instrucción SWITCH a la estructura de repetición DO y se trabaja en una serie de sentencias
    switch (op)
    {
      //Opción 1: La letra U activa el registro de usuarios
      case 'U': usuario_registro(); break;
      // Opción 2: La letra M activa el listado de usuarios
      case 'M': usuario_listado(); break;
      // Opción 3: La letra A activa el registro de libros
      case 'A': actualizar_registro(); break;
      // Opción 4: La letra L activa el listado de libros
      case 'L': listar_registro(); break;
      // Opción 5: La letra P activa el sistema de prestamos
      case 'P': prestamo(); break;
      // Opción 6: La letra R activa el sistema de devolucion
      case 'R': recibir(); break;
    }
    printf("\n");
    system("Pause");
  }
  // Opción 7: La letra F activa el cierre del programa
  while (op != 'F');

  return 0;
}
