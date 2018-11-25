type Tlong=record
       countElem: integer;
       Long :  array [1..101] of string;
     end;
     
//..............................................................................Удаление ведущих нулей
procedure deliteZiro(var s:string; var checkZiro : boolean);
var i, numbNoZiro : integer;
begin
  for i := 1 to length(s) do
  begin
    if (s[i] = '0') and (checkZiro = true)
    then
      numbNoZiro := i
    else
      checkZiro := false
  end;
  Delete(s,1,numbNoZiro);
end;

//..............................................................................Процедура считывания числа
procedure ReadTLong(f1:text; var A:Tlong; var error:boolean);
var
  s, s1:string;
  i, EndLine, count, numbNoZiro:integer;
  checkZiro : boolean;  
begin
//..............................................................................Проверка на максимальное количество символов
  readln(f1, s);
  error := false;
  if length(s) > 300
  then
  begin
    writeln('Количество символов превышает максимум. (300 символов)');
    error:= true;
  end;
//..............................................................................Удаление ведущих нулей
  checkZiro := true;
  deliteZiro(s,checkZiro);
//..............................................................................Проверка на недопустимые символы
  for i := 1 to length(s) do
    if  not (s[i] in ['0'..'9','A','B','C','D','E','F'])
    then 
    begin
      writeln('Недопустимый символ "',s[i],'"');
      error := true;
    end;
//..............................................................................Деление на тройки и запись в массив
  s1 := '';
  EndLine := length(s);
  count := 0;
  if error = false
  then
  begin
    while EndLine > 0 do
    begin
      if EndLine >= 3
      then
      begin
        inc(count);
        s1 := Copy(s ,EndLine - 2, 3);
        A.Long[count] := s1;
        EndLine := EndLine - 3;
      end;
      if EndLine = 2
      then
      begin
        inc(count);
        s1 := Copy(s ,EndLine - 2, 2);
        A.Long  [count] := '0' + s1;
        EndLine := EndLine - 2;
      end;
      if EndLine = 1
      then
      begin
        inc(count);
        s1 := Copy(s ,EndLine - 1, 1);
        A.Long[count] := '00' + s1;
        EndLine := EndLine - 1;
      end;
    end;
    A.countElem := count;//Количество чисел занеcенных в массив
  end;
end;

//..............................................................................Печать числа
procedure PrintTlong(A:Tlong);
var i, j : integer;
    s : string;
    checkZiro : boolean;
begin
  checkZiro := true;
  for i := A.countElem downto 1 do
  begin
    deliteZiro(A.Long[i],checkZiro);
    if (i = 1) and (checkZiro = true)
    then
      A.Long[i] := '0';
    if A.Long[i] = ''
    then
      dec(A.countElem);
    write(A.Long[i]);
  end;
  write('". Число элементов в массиве "', A.countElem,'". ');
  writeln;
end;

//..............................................................................Перевод из char в integer
function CharInt(a:char):integer;
var
  x1,er:integer;
begin
  case a of
    'A': x1 := 10;
    'B': x1 := 11;
    'C': x1 := 12;
    'D': x1 := 13;
    'E': x1 := 14;
    'F': x1 := 15;
    '0'..'9': val(a,x1,er);
  end;
CharInt := x1;
end;
//..............................................................................Перевод из integer в char
function IntChar(a:integer):char;
var
  s:string;
begin
  s := '0123456789ABCDEF';
  IntChar := s[a+1];
end;

//..............................................................................Сложение первого числа элемента массива со вторым числом элемента массива
procedure add3TLong(first:string; second:string; var add:string; var ostatok:integer);
type ElementAdd=record
       ostatok: integer;
       sumChisel: integer;
     end;
var 
  matrica : array [0..15,0..15] of ElementAdd;
  i, j, sum, ostatokSUM:integer;
begin
//..............................................................................Заполнение матрицы сложения в 16-ой системе счисления
  for i := 0 to 15 do
    for j := 0 to 15 do
    begin
      matrica[i,j].ostatok := (i+j) div 16;
      matrica[i,j].sumChisel := (i+j) mod 16;
    end;
    add := '';
//..............................................................................Поразрядное сложение в тройках(элементы массива)
      for i := 3 downto 1 do 
      begin
        ostatokSUM := 0;
        sum := matrica[CharInt(first[i]),CharInt(second[i])].sumChisel + ostatok;
        if sum = 16
        then
          ostatokSUM := 1;
        add :=  IntChar(sum mod 16) + add;
        ostatok := matrica[CharInt(first[i]),CharInt(second[i])].ostatok + ostatokSUM;
      end;
end;

//..............................................................................Процедура добавление остатка в большее число
procedure addOstatokMass(A:Tlong;var add:Tlong; ostatokElem: integer);
var i : integer;
    sumElem : string;
begin
  for i := add.countElem + 1 to A.countElem do
  begin
    add3Tlong(A.Long[i], '000', sumElem, ostatokElem);
    add.Long[i] := sumElem;
    add.countElem := A.countElem;
  end;
  if (i = add.countElem) and (ostatokElem = 1)
  then
  begin
    inc(add.countElem);
    add.Long[add.countElem] := IntChar(ostatokElem);
  end;
end;

{||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||}
procedure addTLong(firstMass:Tlong; secondMass:Tlong; var addMass:Tlong);
var
  ostatokElem, countAdd , elementFirstMass, elementSecondMass, i, countWhile: integer;
  secondMassMore, equallyMass : boolean;
  sumElem : string;
begin
//..............................................................................Сравнение колличества элементов массивов 1 числа со 2
  if firstMass.countElem < secondMass.countElem
  then
  begin
    addMass.countElem := firstMass.countElem;
    secondMassMore := true;
  end
  else
  begin
    addMass.countElem := secondMass.countElem;
    secondMassMore := false;
  end;
//..............................................................................Если количество элементов одинаковое
  equallyMass := false;
  if firstMass.countElem = secondMass.countElem
  then
    equallyMass := true;
//..............................................................................Сложение элементов массивов
  for i := 1 to addMass.countElem do
  begin
    add3TLong(firstMass.Long[i], secondMass.Long[i], sumElem, ostatokElem);
    addMass.Long[i] := sumElem;
  end;
//..............................................................................Если количество элементов одинаково, но остался остаток от суммы
  if (ostatokElem = 1) and (equallyMass = true)
  then
  begin
    inc(addMass.countElem);
    addMass.Long[addMass.countElem] := IntChar(ostatokElem);
  end;
//..............................................................................Прибавление остатка если остались элементы в каком-то из массивов
  if (equallyMass = false)
  then
  begin
//..............................................................................Для второго числа
    if secondMassMore = true
    then
      addOstatokMass(secondMass,addMass, ostatokElem)
//..............................................................................Для первого числа
    else
      addOstatokMass(firstMass,addMass, ostatokElem)
  end;
end;

//..............................................................................Сравнение двух чисел. Если TRUE, то числа равные. Если FALSE, то числа разные
function EQLong(A:Tlong;B:Tlong):boolean;
var i, j : integer;
    err : boolean;
begin
  err := true;
  if A.countElem = B.countElem
  then
    for i := A.countElem downto 1 do
      for j := 1 to 3 do
        if err = false
        then
          EQLong := false
        else
          if CharInt(A.Long[i][j]) = CharInt(B.Long[i][j])
          then
            EQLong := true
          else
            err := false
  else
    EQLong := false
end;

//..............................................................................Сравнение двух чисел. Если TRUE, то первое число больше. Если FALSE, то второе число больше
function LessLong(A:Tlong;B:Tlong;EQLong:boolean):boolean;
var i, j : integer;
    LessInput : byte;
begin
  if EQLong = false
  then
  begin
    if A.countElem > B.countElem
    then
    begin
      LessLong := true;
      LessInput := 1
    end
    else
    begin
      if A.countElem < B.countElem
      then
      begin
        LessLong := false;
        LessInput := 2
      end
      else
        if (LessInput <> 1) and (LessInput <> 2)
        then
          for i := A.countElem downto 1 do
          begin
            if (LessInput <> 1) and (LessInput <> 2)
            then
              for j := 1 to 3 do
              begin
                if (LessInput <> 1) and (LessInput <> 2)
                then
                  if CharInt(A.Long[i][j]) > CharInt(B.Long[i][j])
                  then
                  begin
                    LessLong := true;
                    LessInput := 1
                  end
                  else
                    if CharInt(A.Long[i][j]) < CharInt(B.Long[i][j])
                    then
                    begin
                      LessLong := false;
                      LessInput := 2
                    end;
              end;
          end;
      end
  end;
end;



procedure subTlong(A, B : Tlong;var subMass : Tlong);
var i, j, timesDoSub, bigNumb, ostatok :integer;
    s : string;
begin
  subMass.countElem := 0;
  if A.countElem >= B.countElem 
  then
  begin
    timesDoSub := B.countElem;
    bigNumb := A.countElem;
  end
  else
  begin
    timesDoSub := A.countElem;
    bigNumb := B.countElem;
  end;
  for i := 1 to timesDoSub do
  begin
    if (LessLong(A,B,EQLong(A, B)) = true)// Если TRUE то число А больше чем B. EQLong - Если числа равны между собой то TRUE
    then
    begin
      for j:= 3 downto 1 do
      begin
        if (CharInt(A.Long[i][j]) + ostatok) >= CharInt(B.Long[i][j])
        then
        begin
          s := IntChar(CharInt(A.Long[i][j]) - CharInt(B.Long[i][j]) + ostatok) + s;
          ostatok := 0;
        end
        else
        begin
          s := IntChar(CharInt(A.Long[i][j]) + 16 + ostatok - CharInt(B.Long[i][j])) + s;
          ostatok := -1;
        end;
      end;
      inc(subMass.countElem);
      subMass.Long[i] := s;
      s := '';
    end
    else
    begin
      for j:= 3 downto 1 do
      begin
        if (CharInt(B.Long[i][j]) + ostatok) >= CharInt(A.Long[i][j])
        then
        begin
          s := IntChar(CharInt(B.Long[i][j]) - CharInt(A.Long[i][j]) + ostatok) + s;
          ostatok := 0;
        end
        else
        begin
          s := IntChar(CharInt(B.Long[i][j]) + 16 + ostatok - CharInt(A.Long[i][j])) + s;
          ostatok := -1;
        end;
      end;
      inc(subMass.countElem);
      subMass.Long[i] := s;
      s := '';
    end;
  end;
  for i := timesDoSub + 1 to bigNumb do
  begin
    if (LessLong(A,B,EQLong(A, B)) = true)// Если TRUE то число А больше чем B. EQLong - Если числа равны между собой то TRUE
    then
    begin
      for j:= 3 downto 1 do
      begin
        if (CharInt(A.Long[i][j]) + ostatok) >= CharInt('0')
        then
        begin
          s := IntChar(CharInt(A.Long[i][j]) - CharInt('0') + ostatok) + s;
          ostatok := 0;
        end
        else
        begin
          s := IntChar(CharInt(A.Long[i][j]) + 16 + ostatok - CharInt('0')) + s;
          ostatok := -1;
        end;
      end;
      inc(subMass.countElem);
      subMass.Long[i] := s;
      s := '';
    end
    else
    begin
      for j:= 3 downto 1 do
      begin
        if (CharInt(B.Long[i][j]) + ostatok) >= CharInt('0')
        then
        begin
          s := IntChar(CharInt(B.Long[i][j]) - CharInt('0') + ostatok) + s;
          ostatok := 0;
        end
        else
        begin
          s := IntChar(CharInt(B.Long[i][j]) + 16 + ostatok - CharInt('0')) + s;
          ostatok := -1;
        end;
      end;
      inc(subMass.countElem);
      subMass.Long[i] := s;
      s := '';
    end;
  end;
end;


var
  f1:text;
  i, numbChisla:integer;
  firstMass, secondMass, addMass, subMass :Tlong;
  error, big1 :boolean;
begin
  assign(f1, 'chisla.txt');
  reset(f1);
  ReadTLong(f1, firstMass, error);
  ReadTLong(f1, secondMass, error);
  addTLong (firstMass, secondMass, addMass);
  subTLong (firstMass, secondMass, subMass);
  write('Первое число = "');    
  PrintTlong(firstMass);
  write('Второе число = "');
  PrintTlong(secondMass);
  write('Сумма двух чисел = "');
  PrintTlong(addMass);
  
    if (LessLong(firstMass, secondMass, EQLong(firstMass, secondMass)) = true)
    then
      write('Разность двух чисел = "')
    else
      if EQLong(firstMass, secondMass) = true
      then
        write('Разность двух чисел = "')
      else
        write('Разность двух чисел = "-');
    PrintTlong(subMass);
  
  
  big1 := EQLong(firstMass, secondMass);
  if big1 = true
  then
    writeln('Два числа равны EQLong')
  else
  begin
    writeln('Два числа не равны EQLong');
    if (LessLong(firstMass, secondMass, big1) = true)
    then
      writeln('Первое число больше LessLong')
    else
      writeln('Второе число больше LessLong');
   end;
      
      
end.