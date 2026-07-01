
/**
 * Escreva uma descrição da classe SpotifUM aqui.
 * 
 * @author (seu nome) 
 * @version (um número da versão ou uma data)
 */
import java.io.Serializable;
import java.util.*;
import java.util.List;

public class SpotifUM implements Serializable {
    private List<Musica> musicas;
    private List<Utilizador> utilizadores;
    private List<Album> albuns;
    private List<Playlist> playlists;
    
    public SpotifUM() {
        musicas = new ArrayList<>();
        utilizadores = new ArrayList<>();
        albuns = new ArrayList<>();
        playlists = new ArrayList<>();
    }
    
    // Métodos para adicionar 
    public void adicionarMusica(Musica musica) {
        musicas.add(musica);
    }
    
    public void adicionarUtilizador(Utilizador utilizador) {
        utilizadores.add(utilizador);
    }
    
    public void adicionarAlbum(Album album) {
        albuns.add(album);
    }
    
    public void adicionarPlaylist(Playlist playlist) {
        playlists.add(playlist);
    }
    
    // Método para reproduzir musica
    public void reproduzirMusicaParaUtilizador(Utilizador u, Musica m) {
        u.reproduzirMusica(m);
    }
    
    // MÉTODOS DE ESTATÍSTICA
    
    // Exemplo: A música mais reproduzida
    public Musica getMusicaMaisReproduzida() {
        Musica maisReproduzida = null;
        int maxReproducoes = 0;
        for (Musica m : musicas) {
            if(m.contadorReproducoes > maxReproducoes) {
                maxReproducoes = m.contadorReproducoes;
                maisReproduzida = m;
            }
        }
        return maisReproduzida;
    }
    
    // Outros métodos para estatísticas:
    // - Intérprete mais escutado
    // - Utilizador que mais ouviu música
    // - Utilizador com mais pontos
    // - Tipo de música mais reproduzida
    // - Contabilização de playlists públicas, etc.
    
    // MÉTODOS DE SALVAGUAR / CARREGAR ESTADO
    
}
