
/**
 * Escreva uma descrição da classe Musica aqui.
 * 
 * @author (seu nome) 
 * @version (um número da versão ou uma data)
 */

import java.io.Serializable;
import java.util.*;
import java.util.List;

public class Musica implements Serializable {
    // Atributos da música
    protected String nome;
    protected String interprete;
    protected String editora;
    protected String letra;
    protected List<String> linhasMusicais; // linhas representativas do som (texto)
    protected String genero;
    protected int duracaoSegundos;
    protected int contadorReproducoes;
    protected Album album; // associação com um álbum (opcional)

    public Musica(String nome, String interprete, String editora, String letra,
                  List<String> linhasMusicais, String genero, int duracaoSegundos, Album album) {
        this.nome = nome;
        this.interprete = interprete;
        this.editora = editora;
        this.letra = letra;
        this.linhasMusicais = linhasMusicais;
        this.genero = genero;
        this.duracaoSegundos = duracaoSegundos;
        this.contadorReproducoes = 0;
        this.album = album;
    }

    // Método para reproduzir a música
    public void reproduzir() {
        System.out.println("Reproduzindo: " + this.nome);
        System.out.println("Letra: " + this.letra);
        contadorReproducoes++;
        // Implementar outras lógicas se necessário.
    }

    // Getters e setters FAZER !!!!!!!!!!!!!!!!!
}
