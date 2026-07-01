
/**
 * Escreva uma descrição da classe Utilizador aqui.
 * 
 * @author (seu nome) 
 * @version (um número da versão ou uma data)
 */

import java.io.Serializable;
import java.util.*;
import java.util.List;

public abstract class Utilizador implements Serializable {
    protected String nome;
    protected String email;
    protected String morada;
    protected int pontos;
    // Talvez colocar mais informacoes tipo histórico de reproduções, bibliotecas, etc.
    
    public Utilizador(String nome, String email, String morada) {
        this.nome = nome;
        this.email = email;
        this.morada = morada;
        this.pontos = 0;
    }
    
    // Método para reproduzir uma música (possivelmente incrementando pontos)
    public abstract void reproduzirMusica(Musica musica);
    
    // Getters e setters FAZER !!!!!!!!
}
