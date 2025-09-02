package org.example;
import org.apache.jena.ontology.OntModel;
import org.apache.jena.query.QuerySolution;
import org.apache.jena.query.ResultSet;
import org.apache.jena.rdf.model.ModelFactory;

//Bryan Mendoza
public class Main {

    public static void main (String[] args) {
        //Crear Ontología
        //realizarOntologia(); //Parte 1 y 2

        Ontologia ont = leerModelo("Modelo2.ttl"); //Parte 2 y 3 -- solo cambiar nombre del archivo
        //consultaHombresMayoresEdad(45, ont); //parte 3

        ont.activarInferenciaOWL(); //activar la inferencia  - Parte 4
        hijosPersona1(ont); //parte 4
    }

    public static void hijosPersona1(Ontologia ontologia){
        String queryString = String.format("""          
                PREFIX ont: <http://example.org/>

                SELECT ?nombre
                        WHERE {
                        ?p ont:esHijoDe ont:Persona1;
                              ont:tieneNombre ?nombre.
                        }
                    """);

        ResultSet results = ontologia.consultasSPARQL(queryString);
        System.out.println("Los hijos de la persona 1 son:");
        while (results.hasNext()) {
            QuerySolution sol = results.next();
            System.out.println("- " + sol.getLiteral("nombre").getString());
        }
    }

    public static void consultaHombresMayoresEdad(int edad, Ontologia ontologia){
        String queryString = String.format("""          
                PREFIX ont: <http://example.org/>

                SELECT ?nombre
                        WHERE {
                        ?p a ont:Hombre;
                              ont:tieneNombre ?nombre;
                              ont:tieneEdad ?e.
                        FILTER(?e > %d)
                        }
                    """,edad);

        ResultSet results = ontologia.consultasSPARQL(queryString);
        System.out.println("Los hombres mayores a 45 años son:");
        while (results.hasNext()) {
            QuerySolution sol = results.next();
            System.out.println("- " + sol.getLiteral("nombre").getString());
        }
    }

    public static Ontologia leerModelo(String nameArchivo){
        LeerModelo leerModelo = new LeerModelo();
        OntModel model = leerModelo.leerModelo(nameArchivo);
        //model.write(System.out, "RDF/XML-ABBREV");
        Ontologia ontologia = new Ontologia("http://example.org/", model);
        return ontologia;
    }
    public static void realizarOntologia (){
        Ontologia ontologia = new Ontologia("http://example.org/", ModelFactory.createOntologyModel());
        OntModel model = ontologia.getModel();
        ontologia.construirModelo();
        model.write(System.out, "RDF/XML-ABBREV");  //imprimir ontologia
        ontologia.guardarModelo("Modelo2.ttl");
    }
}