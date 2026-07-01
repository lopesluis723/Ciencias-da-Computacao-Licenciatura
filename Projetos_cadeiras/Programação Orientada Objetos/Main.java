
/**
 * Escreva uma descrição da classe Main aqui.
 * 
 * @author (seu nome) 
 * @version (um número da versão ou uma data)
 */

import java.io.Serializable;
import java.util.*;
import java.util.List;

public class Main {
    public static void main(String[] args) {
        // Criação do sistema
        SpotifUM spotifUM = new SpotifUM();
        
        // Criação de um álbum (exemplo)
        Album albumExemplo = new Album("Álbum Exemplo", "Artista Exemplo");
        spotifUM.adicionarAlbum(albumExemplo);
        
        // Criação de músicas
        List<String> linhas = Arrays.asList("linha 1", "linha 2", "linha 3");
        Musica musica1 = new Musica("Música 1", "Interprete 1", "Editora 1", "Letra da música 1", linhas, "Pop", 210, albumExemplo);
        Musica musica2 = new MusicaExplicita("Música 2", "Interprete 2", "Editora 2", "Letra da música 2", linhas, "Rock", 190, albumExemplo);
        albumExemplo.adicionarMusica(musica1);
        albumExemplo.adicionarMusica(musica2);
        spotifUM.adicionarMusica(musica1);
        spotifUM.adicionarMusica(musica2);
        
        // Criação de utilizadores
        Utilizador u1 = new UtilizadorOcasional("João", "joao@email.com", "Rua A");
        Utilizador u2 = new UtilizadorPremium("Maria", "maria@email.com", "Rua B", new PlanoPremiumBase());
        spotifUM.adicionarUtilizador(u1);
        spotifUM.adicionarUtilizador(u2);
        
        // Criação de uma playlist e adição de músicas
        Playlist playlist1 = new PlaylistAleatoria("Playlist Aleatória", true);
        playlist1.adicionarMusica(musica1);
        playlist1.adicionarMusica(musica2);
        spotifUM.adicionarPlaylist(playlist1);
        
        // Simulação de reprodução
        spotifUM.reproduzirMusicaParaUtilizador(u1, musica1);
        spotifUM.reproduzirMusicaParaUtilizador(u2, musica2);
        
        // Exemplo de estatística
        Musica top = spotifUM.getMusicaMaisReproduzida();
        if(top != null){
            System.out.println("Música mais reproduzida: " + top.nome);
        }
        
        // Não sei como mas tipo fazer uma cena para  guardar o estado num ficheiro(ler melhor o que diz no pdf do trabalho pq ainda n entendi muito bem)
    }
}
