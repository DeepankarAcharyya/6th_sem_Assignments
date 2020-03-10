import java.io.File;
import java.io.FileWriter;
import java.io.IOException;

class file_handling{
    public static void main(String[] args) throws IOException{
         try{
             File myObj=new File("Output.txt");
             if(myObj.createNewFile()){
                 System.out.println("File Created : "+myObj.getName());
             }
             else{
                 System.out.println("File already exists.");
             }
             
             FileWriter file=new FileWriter("Output.txt");
             file.write("Testing!!!");
             file.close();
             
            }
        catch (IOException e){
             System.out.println("An error occured.");
             e.printStackTrace();
         }
    }
}