#!/usr/bin/perl
#**************************************************************
#         		Pontificia Universidad Javeriana
#     Autor: Grupo Beta
#     Fecha: Mayo 2024
#     Materia: Sistemas Operativos
#     Tema: Taller de Evaluación de Rendimiento
#     Fichero: script automatización ejecución por lotes 
#****************************************************************/

$Path = `pwd`;
chomp($Path);

#nombre del ejecutable 
$Nombre_Ejecutable = "mmClasicaOpenMP";
#tamaño de las matrices a evaluar
@Size_Matriz = ("4","6","8");
#numero de hilos o procesos a evaluar	
@Num_Hilos = (1,2,3);
#cantidad de repeticiones
$Repeticiones = 30;

#ejecuta el programa para cada tamaño de matriz y cada cantidad de hilos
	foreach $size (@Size_Matriz){
		foreach $hilo (@Num_Hilos) {
			$file = "$Path/resultadosOpenMP/$Nombre_Ejecutable-".$size."-Hilos-".$hilo.".dat";
				for ($i=0; $i<$Repeticiones; $i++) {
			#guardar el resultado en otra carpeta
				system("$Path/$Nombre_Ejecutable $size $hilo  >> $file");
				printf("$Path/$Nombre_Ejecutable $size $hilo \n");
				}
		#cierre del archivo
		close($file);
	
	}
}
