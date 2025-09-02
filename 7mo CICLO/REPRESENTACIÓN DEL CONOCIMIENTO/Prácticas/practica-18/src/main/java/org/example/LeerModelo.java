package org.example;

import org.apache.jena.ontology.OntModel;
import org.apache.jena.ontology.OntModelSpec;
import org.apache.jena.rdf.model.ModelFactory;
import org.apache.jena.util.FileManager;

public class LeerModelo {
    public OntModel leerModelo (String nameArchivo) {
        OntModel modelo = ModelFactory.createOntologyModel(OntModelSpec.OWL_MEM);
        FileManager.get().readModel(modelo, nameArchivo);
        System.out.println("Modelo "+nameArchivo+" leído con éxito!");
        return modelo;
        //modelo.write(System.out, "RDF/XML-ABBREV");
    }
}
