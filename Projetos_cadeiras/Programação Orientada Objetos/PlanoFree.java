
/**
 * Escreva uma descrição da classe PlanoFree aqui.
 * 
 * @author (seu nome) 
 * @version (um número da versão ou uma data)
 */

import java.io.Serializable;
import java.util.*;
import java.util.List;

public class PlanoFree implements PlanoSubscricao {
    @Override
    public int calcularPontosReproducao(int pontosAtuais) {
        return 5;
    }
    @Override
    public String getNomePlano() {
        return "Free";
    }
}
