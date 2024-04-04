package Lab2Var5;

import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.util.*;

public class Main {
    public static void main(String[] args) throws java.io.IOException, java.lang.Exception {
	    // Ініціалізуємо скінченний автомат
        Machine machine = new Machine("\\MachineDefinition2.txt");
        // Ініціалізуємо w0
        Scanner scan= new Scanner(System.in);
        System.out.println("Введіть слово w0: ");
        String w0 = scan.nextLine();
        // Знаходимо множину досяжних станів для початкового стану
        Map<Integer, String> attainableStates = machine.attainableStates(machine.getInitialState());
        // Проходимо по множині досяжних станів та вилучаємо ті, починаючи з яких автомат не розпізнає w0
        Iterator iterator = attainableStates.keySet().iterator();
        while (iterator.hasNext()) {
            Integer state = (Integer)iterator.next();
            if (!machine.execute(w0, state)) iterator.remove();
        }
        // Виводимо результати
        if (attainableStates.isEmpty())
            System.out.println("Слово w1w0 НЕ було розпізнано!");
        else{
            System.out.println("Слово w1w0 було розпізнано! Приклади допустимих w1: ");
            for (Integer state : attainableStates.keySet())
                System.out.println(" [" + attainableStates.get(state) + "] Тоді w0 почнеться зі стану " + state);
        }
    }
}

class Machine {
    private static Integer alphabetSize;
    private static Integer statesNumber;
    private static Integer initialState;
    private static List<Integer> finalStates = new LinkedList<Integer>();
    // Контейнер функцій переходів
    private static HashMap<Integer, HashMap<Character, Integer>> transitionRules = new HashMap<Integer, HashMap<Character, Integer>>();

    // Конструктор формує автомат, заповнюючи початкові дані
    public Machine(String fileName) throws IOException{
        String filePath = new File("").getAbsolutePath();
        FileReader file = new FileReader(filePath + fileName);
        Scanner scan = new Scanner(file);
        alphabetSize = scan.nextInt();
        statesNumber = scan.nextInt();
        initialState = scan.nextInt();
        // Зберігаємо множину фінальних станів
        Integer finalStatesNumber = scan.nextInt();
        for (Integer i = 0; i < finalStatesNumber; ++i)
            finalStates.add(scan.nextInt());
        // Зберігаємо множину функцій переходів
        while (scan.hasNextLine()) {
            Integer curState = scan.nextInt();
            if (transitionRules.containsKey(curState)){  // Якщо з цим станом вже пов'язана функція, додаємо ще одну
                transitionRules.get(curState).put(scan.next().charAt(0),scan.nextInt());
            }
            else{
                HashMap<Character, Integer> nextState = new HashMap<Character, Integer>();
                nextState.put(scan.next().charAt(0),scan.nextInt());
                transitionRules.put(curState, nextState);
            }
        }
        file.close();
    }

    // Виконання автомату
    public static boolean execute(String word, Integer startingState) throws Exception {
        Integer currentState = startingState;
        for (int i = 0; i < word.length(); i++){
            Character symbol = word.charAt(i);
            if (transitionRules.get(currentState).get(symbol) != null)
                currentState = transitionRules.get(currentState).get(symbol);
            else
                return false;
        }
        // Перевіряємо, чи є поточний стан фінальним
        return finalStates.contains(currentState);
    }

    // Повертає значення початкового стану
    public static Integer getInitialState(){
        return initialState;
    }

    // Поертає множину усіх досяжний станів та слова, що ведуть до цих станів
    // Вигляд : <досяжний стан, приклад слова>
    public static HashMap<Integer, String> attainableStates (Integer startingState){
        HashMap<Integer, String> resultContainer = new HashMap<Integer, String>();
        findAttainable(startingState, resultContainer, "");
        return resultContainer;
    }

    // Рекурсією проходимо по ланцюжкам функцій переходів, заносимо інформацію про вже пройдені стани
    private static void findAttainable(Integer startingState, HashMap<Integer, String> resultContainer, String guideWord){
        Integer currentState = startingState, nextState;
        for(Character symbol : transitionRules.get(currentState).keySet()){
            nextState = transitionRules.get(currentState).get(symbol);
            if (!resultContainer.containsKey(nextState)){
                guideWord += symbol;
                resultContainer.put(nextState, guideWord);
                findAttainable(nextState, resultContainer, guideWord);
                guideWord = guideWord.substring(0, guideWord.length() - 1);
            }
        }
    }
}