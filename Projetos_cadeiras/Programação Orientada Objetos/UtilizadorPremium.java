
/**
 * Escreva uma descrição da classe UtilizadorPremium aqui.
 * 
 * @author (seu nome) 
 * @version (um número da versão ou uma data)
 */

import java.io.Serializable;
import java.util.*;
import java.util.List;

public class UtilizadorPremium extends Utilizador {
    private PlanoSubscricao plano;
    // Listas, biblioteca, etc.
    private List<Playlist> minhasPlaylists;
    
    public UtilizadorPremium(String nome, String email, String morada, PlanoSubscricao plano) {
        super(nome, email, morada);
        this.plano = plano;
        this.minhasPlaylists = new ArrayList<>();
    }
    
    @Override
    public void reproduzirMusica(Musica musica) {
        musica.reproduzir();
        // A quantidade de pontos pode vir do plano associado
        pontos += plano.calcularPontosReproducao(pontos);
    }
    
    public void criarPlaylist(Playlist playlist) {
        minhasPlaylists.add(playlist);
    }
    
    // Outros métodos para gerenciar a biblioteca e playlists
}
