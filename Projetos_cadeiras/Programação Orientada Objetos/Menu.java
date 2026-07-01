
/**
 * Escreva uma descrição da classe Menu aqui.
 * 
 * @author (seu nome) 
 * @version (um número da versão ou uma data)
 */

import java.io.Serializable;
import java.util.*;
import java.util.List;
import java.util.Scanner;

public class Menu {
    // Instância do sistema que gerencia as entidades (SpotifUM)
    private SpotifUM spotifUM;
    // Scanner para ler a entrada do usuário
    private Scanner scanner;

    // Construtor: inicializa o sistema e o Scanner
    public Menu() {
        spotifUM = new SpotifUM();
        scanner = new Scanner(System.in);
    }

    // Método que exibe o menu e controla a navegação
    public void exibirMenu() {
        int opcao = -1;
        do {
            System.out.println("----- Menu SpotifUM -----");
            System.out.println("1. Adicionar Utilizador");
            System.out.println("2. Adicionar Música");
            System.out.println("3. Adicionar Álbum");
            System.out.println("4. Adicionar Playlist");
            System.out.println("5. Reproduzir Conteúdo");
            System.out.println("6. Exibir Estatísticas");
            System.out.println("7. Salvar Estado");
            System.out.println("8. Carregar Estado");
            System.out.println("0. Sair");
            System.out.print("Escolha uma opção: ");

            try {
                opcao = Integer.parseInt(scanner.nextLine());
            } catch (NumberFormatException e) {
                System.out.println("Opção inválida. Por favor, insira um número.");
                continue;
            }
            
            switch (opcao) {
                case 1:
                    adicionarUtilizador();
                    break;
                case 2:
                    adicionarMusica();
                    break;
                case 3:
                    adicionarAlbum();
                    break;
                case 4:
                    adicionarPlaylist();
                    break;
                case 5:
                    reproduzirConteudo();
                    break;
                case 6:
                    exibirEstatisticas();
                    break;
                case 7:
                    salvarEstado();
                    break;
                case 8:
                    carregarEstado();
                    break;
                case 0:
                    System.out.println("Saindo do sistema...");
                    break;
                default:
                    System.out.println("Opção inválida. Tente novamente.");
            }
        } while (opcao != 0);
    }

    // Métodos auxiliares esqueleto que deverão ser implementados conforme a lógica do sistema

    // Método para adicionar um utilizador ao sistema
    private void adicionarUtilizador() {
         System.out.println("Adicionando utilizador...");
         // Implementar lógica para criar e adicionar um novo utilizador a spotifUM
    }
    
    // Método para adicionar uma música ao sistema
    private void adicionarMusica() {
         System.out.println("Adicionando música...");
         // Implementar lógica para criar e adicionar uma nova música a spotifUM
    }
    
    // Método para adicionar um álbum ao sistema
    private void adicionarAlbum() {
         System.out.println("Adicionando álbum...");
         // Implementar lógica para criar e adicionar um novo álbum a spotifUM
    }
    
    // Método para adicionar uma playlist ao sistema
    private void adicionarPlaylist() {
         System.out.println("Adicionando playlist...");
         // Implementar lógica para criar e adicionar uma nova playlist a spotifUM
    }
    
    // Método para reproduzir conteúdo (música ou playlist)
    private void reproduzirConteudo() {
         System.out.println("Reproduzindo conteúdo...");
         // Implementar a lógica para selecionar e reproduzir uma música/playlist
    }
    
    // Método para exibir estatísticas do sistema
    private void exibirEstatisticas() {
         System.out.println("Exibindo estatísticas...");
         // Implementar a exibição de estatísticas, como música mais reproduzida, etc.
    }
    
    // Método para salvar o estado atual do sistema em um arquivo (serialização)
    private void salvarEstado() {
         System.out.println("Salvando estado...");
         // Implementar lógica para serializar o objeto spotifUM e salvar em arquivo
    }
    
    // Método para carregar o estado do sistema a partir de um arquivo (desserialização)
    private void carregarEstado() {
         System.out.println("Carregando estado...");
         // Implementar lógica para ler o arquivo e desserializar o objeto spotifUM
    }

    // Método main para iniciar a interface do menu
    public static void main(String[] args) {
        Menu menu = new Menu();
        menu.exibirMenu();
    }
}
