#
# Eliminar archivos ejecutables
# source config.sh
#
clean()
{
   for file in *
   do
      #echo $file
      if [ -f $file -a -x $file -a $file != "config.sh" -a "$file" == "${file/\./}" ]
      then
         echo "rm -f $file"
         rm -f $file
      fi
   done
}
