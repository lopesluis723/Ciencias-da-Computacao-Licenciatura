
/**
 * Escreva uma descrição da classe PlaylistAleatoria aqui.
 * 
 * @author (seu nome) 
 * @version (um número da versão ou uma data)
 */

import java.io.Serializable;
import java.util.*;
import java.util.List;

public class PlaylistAleatoria extends Playlist {
    
    public PlaylistAleatoria(String nome, boolean publica) {
        super(nome, publica);
    }
    
    @Override
    public void reproduzirPlaylist() {
        // Embaralhar a lista e reproduzir cada música
        List<Musica> copia = new ArrayList<>(musicas);
        Collections.shuffle(copia);
        for(Musica m : copia) {
            m.reproduzir();
        }
    }
}
