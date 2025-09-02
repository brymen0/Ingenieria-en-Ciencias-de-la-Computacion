package org.example;

import org.apache.jena.ontology.*;
import org.apache.jena.rdf.model.ModelFactory;
import org.apache.jena.rdf.model.RDFList;
import org.apache.jena.rdf.model.RDFNode;
import org.apache.jena.rdf.model.Resource;
import org.apache.jena.util.FileManager;
import org.apache.jena.vocabulary.OWL;
import org.apache.jena.vocabulary.RDF;
import org.apache.jena.vocabulary.XSD;
import org.apache.jena.query.*;
import org.apache.jena.rdf.model.InfModel;
import org.apache.jena.reasoner.ReasonerRegistry;

import java.io.FileOutputStream;
import java.util.HashMap;
import java.util.Map;

public class Ontologia {
    private final OntModel model;
    private InfModel infModel = null;
    private final String nsOntology;

    public Ontologia(String namespace, OntModel model) {
        //this.model = ModelFactory.createOntologyModel();
        this.model = model;
        this.nsOntology = namespace;
    }

    public OntModel getModel() {
        return model;
    }

    public InfModel getInfModel() {
        if (infModel == null) {
            infModel = ModelFactory.createInfModel(ReasonerRegistry.getOWLReasoner(), model);
        }
        return infModel;
    }
    public void construirModelo(){
        Map<String, OntClass> clases = createClass();
        OntClass Persona = clases.get("Persona");
        OntClass Hombre = clases.get("Hombre");
        OntClass Mujer = clases.get("Mujer");

        Map<String, ObjectProperty> objectProperties = createObjectProperties(Persona);
        Map<String, DatatypeProperty> dataProperties = createDataProperties(Persona);
        setCaracteristicasPropiedades(objectProperties); //Parte 2
        createInstances(Hombre, Mujer);

        Map<String, Individual> personas = getPersonas();
        definirPersonasDiferentes(personas);
        incorporarConocimiento(personas, objectProperties);
    }

    public void activarInferenciaOWL() {
        InfModel infModel = ModelFactory.createInfModel(
                ReasonerRegistry.getOWLReasoner(), this.model
        );

        OntModel modeloInferido = ModelFactory.createOntologyModel(OntModelSpec.OWL_MEM); //crea otro modelo pero este es inferido
        modeloInferido.add(infModel);

        // Reemplazar el modelo original
        this.model.removeAll();
        this.model.add(modeloInferido);
    }

    public void guardarModelo (String nombreArchivo) {
        try (FileOutputStream out = new FileOutputStream(nombreArchivo)) {
            model.write(out, "TURTLE");
            System.out.println("Modelo guardado exitosamente en "+nombreArchivo);
        } catch (Exception e) {
            e.printStackTrace();
        }

    }
    private void incorporarConocimiento(Map<String, Individual> personas, Map<String, ObjectProperty> objectProperties) {
        setTripelta(personas.get("Persona1"), objectProperties.get("esPadreDe"), personas.get("Persona2"));
        setTripelta(personas.get("Persona1"), objectProperties.get("esPadreDe"), personas.get("Persona3"));
        setTripelta(personas.get("Persona2"), objectProperties.get("esHermanoDe"), personas.get("Persona3"));
        setTripelta(personas.get("Persona4"), objectProperties.get("esCasadoCon"), personas.get("Persona2"));
    }

    private void setTripelta(Individual sujeto, ObjectProperty objeto, Individual predicado) {
        sujeto.addProperty(objeto, predicado);
    }
    public ResultSet consultasSPARQL(String queryString) {
        Query query = QueryFactory.create(queryString);
        try (QueryExecution qexec = QueryExecutionFactory.create(query, this.model)) {
            ResultSet results = qexec.execSelect();
            //ResultSetFormatter.out(System.out, results);
            return ResultSetFactory.copyResults(results);
        }
    }
    private void setCaracteristicasPropiedades(Map<String, ObjectProperty> objectProperties){
        ObjectProperty esHermanoDe = objectProperties.get("esHermanoDe");
        ObjectProperty esCasadoCon = objectProperties.get("esCasadoCon");
        ObjectProperty esPadreDe = objectProperties.get("esPadreDe");
        ObjectProperty esHijoDe = objectProperties.get("esHijoDe");

        esHermanoDe.addProperty(RDF.type, OWL.SymmetricProperty);
        esCasadoCon.addProperty(RDF.type, OWL.SymmetricProperty);

        esPadreDe.addInverseOf(esHijoDe);
    }

    private Map<String, Individual> getPersonas() {
        Map<String, Individual> personas = new HashMap<>();

        Individual Persona1 = this.model.getIndividual(nsOntology+"Persona1");
        Individual Persona2 = this.model.getIndividual(nsOntology+"Persona2");
        Individual Persona3 = this.model.getIndividual(nsOntology+"Persona3");
        Individual Persona4 = this.model.getIndividual(nsOntology+"Persona4");

        personas.put("Persona1", Persona1);
        personas.put("Persona2", Persona2);
        personas.put("Persona3", Persona3);
        personas.put("Persona4", Persona4);
        return personas;
    }
    private void definirPersonasDiferentes (Map<String, Individual> personas){
        RDFList lista = this.model.createList(new RDFNode[] {
                personas.get("Persona1"), personas.get("Persona2"), personas.get("Persona3"), personas.get("Persona4")
        });
        Resource allDifferent = this.model.createResource(OWL.AllDifferent);
        allDifferent.addProperty(OWL.distinctMembers, lista);
    }

    private void asignarDatosPersona(Individual persona, String nombre, int edad){
        DatatypeProperty tieneNombre = this.model.getDatatypeProperty(nsOntology + "tieneNombre");
        DatatypeProperty tieneEdad = this.model.getDatatypeProperty(nsOntology + "tieneEdad");

        persona.addProperty(tieneNombre, nombre);
        persona.addProperty(tieneEdad, this.model.createTypedLiteral(edad));
    }

    private void createInstances (OntClass Hombre, OntClass Mujer){
        Individual Persona1 = this.model.createIndividual(nsOntology+"Persona1", Hombre);
        Individual Persona2 = this.model.createIndividual(nsOntology+"Persona2", Hombre);
        Individual Persona3 = this.model.createIndividual(nsOntology+"Persona3", Hombre);
        Individual Persona4 = this.model.createIndividual(nsOntology+"Persona4", Mujer);

        asignarDatosPersona(Persona1, "Juan Perez", 75);
        asignarDatosPersona(Persona2, "Angel Perez", 46);
        asignarDatosPersona(Persona3, "Vinicio Perez", 44);

        DatatypeProperty tieneNombre = this.model.getDatatypeProperty(nsOntology + "tieneNombre");
        Persona4.addProperty(tieneNombre, "Rosario Castillo");
    }

    private Map<String, DatatypeProperty> createDataProperties (OntClass Persona){
        Map<String, DatatypeProperty> dataProperties = new HashMap<>();

        DatatypeProperty tieneNombre = this.model.createDatatypeProperty(nsOntology+"tieneNombre");
        tieneNombre.addDomain(Persona);
        tieneNombre.addRange(XSD.xstring);
        DatatypeProperty tieneEdad = this.model.createDatatypeProperty(nsOntology+"tieneEdad");
        tieneEdad.addDomain(Persona);
        tieneEdad.addRange(XSD.xint);

        dataProperties.put("tieneNombre", tieneNombre);
        dataProperties.put("tieneEdad", tieneEdad);

        return dataProperties;
    }
    private Map<String, ObjectProperty> createObjectProperties (OntClass Persona) {
        Map<String, ObjectProperty> objectProperties = new HashMap<>();

        ObjectProperty esCasadoCon = this.model.createObjectProperty(nsOntology+"esCasadoCon");
        esCasadoCon.addDomain(Persona);
        esCasadoCon.addRange(Persona);

        ObjectProperty esHermanoDe = this.model.createObjectProperty(nsOntology+"esHermanoDe");
        esHermanoDe.addDomain(Persona);
        esHermanoDe.addRange(Persona);

        ObjectProperty esHijoDe = this.model.createObjectProperty(nsOntology+"esHijoDe");
        esHijoDe.addDomain(Persona);
        esHijoDe.addRange(Persona);

        ObjectProperty esPadreDe = this.model.createObjectProperty(nsOntology+"esPadreDe");
        esPadreDe.addDomain(Persona);
        esPadreDe.addRange(Persona);

        objectProperties.put("esCasadoCon", esCasadoCon);
        objectProperties.put("esHermanoDe", esHermanoDe);
        objectProperties.put("esHijoDe", esHijoDe);
        objectProperties.put("esPadreDe", esPadreDe);

        return objectProperties;
    }

    private Map<String, OntClass> createClass (){
        Map <String, OntClass> clases = new HashMap<>();
        OntClass Persona = this.model.createClass(nsOntology+"Persona");
        OntClass Hombre = this.model.createClass(nsOntology+"Hombre");
        OntClass Mujer = this.model.createClass(nsOntology+"Mujer");

        Persona.addSubClass(Hombre);
        Persona.addSubClass(Mujer);

        RDFList unionList = this.model.createList(new Resource[]{Hombre, Mujer});
        OntClass unionHM = this.model.createUnionClass(null, unionList);
        Persona.setEquivalentClass(unionHM);

        Hombre.addDisjointWith(Mujer);

        clases.put("Persona", Persona);
        clases.put("Hombre", Hombre);
        clases.put("Mujer", Mujer);

        return clases;
    }
}
