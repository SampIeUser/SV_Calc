#include "calc_actions.h"
#include <cmath>
#include <QMap>

Calc_actions::Calc_actions()
{

}
// pow -> sqrt -> devide -> multiply -> adding
QString Calc_actions::evaluate(QString data)
{
  //lists for found expressions
  QStringList pow_list;
  QStringList sqrt_list;
  QStringList div_list;
  QStringList mult_list;
  QStringList add_list;
  // regular expressions for splitting expression and solveing part by part
  QRegularExpression expr_pow("[S]?[-+*\\/]*\\d*[.]?\\d*\\^[-]?\\d*[.]?\\d*");
  QRegularExpression expr_sqrt("[S]?[-+*\\/]*\\d*[.]?\\d*[S][-]?\\d*[.]?\\d*");
  QRegularExpression expr_div("[-]?\\d*[.]?\\d*\\/[-]?\\d*[.]?\\d*");
  QRegularExpression expr_mult("[-]?\\d*[.]?\\d*\\*[-]?\\d*[.]?\\d*");
  QRegularExpression expr_add("[-]?\\d*[.]?\\d*[^\\-+s]");

  // проверка является ли выражение единственным. если да, то добавить вначале минус, для верных проверок


  // if it's a simple expression - add minus (if needed), for correct checking
  QRegularExpressionMatchIterator i;
  // correcting for pow and sqrt checks
  if (data[0] == '-')
  {
      data = '-'+data;
  }
// getting pow's
  i = expr_pow.globalMatch(data);
  while (i.hasNext()) {
      QRegularExpressionMatch match = i.next();      
      pow_list << match.captured(0);
  }
  // now i have list with pows
  if (pow_list.length() != 0)
  {
      QMap pow_list_solved = pow(pow_list);
        if (!pow_list_solved.contains("Error"))
        {
      // replaceing with solved
      QMapIterator<QString, QString> i(pow_list_solved);
        while (i.hasNext())
        {            
            i.next();
            if (i.key().length() == data.length()-1)
            {
                data.remove(0,1);
            }
            data.replace(i.key(), i.value());
        }
         // pows found and replaced (it they were)
        }
        else
        {
            return pow_list_solved.value("Error");
        }
  }

  // getting sqrt's
     i = expr_sqrt.globalMatch(data);

  while (i.hasNext())
  {
      QRegularExpressionMatch match = i.next();
      sqrt_list << match.captured(0);
  }

   if (sqrt_list.length() != 0)
   {
       QMap sqrt_list_solved = sqrt(sqrt_list);
       if (!sqrt_list_solved.contains("Error"))
       {
           // replaceing with solved
           QMapIterator<QString, QString> i(sqrt_list_solved);
             while (i.hasNext())
             {
                 i.next();
                 data.replace(i.key(), i.value());
             }
       }
       else
       {
           return sqrt_list_solved.value("Error");
       }
   }

   // devide
   i = expr_div.globalMatch(data);
   while (i.hasNext()) {
       QRegularExpressionMatch match = i.next();
       div_list << match.captured(0);
   }
   if (div_list.length() != 0)
   {
       QString div_sol;
       foreach (div_sol, div_list)
       {
           QStringList div;
           div << div_sol.split('/');
           double devide = div[0].toDouble()/div[1].toDouble();
           QString div_sol_solved = QString::number(devide, 'f', 4);
           data.replace(div_sol,div_sol_solved);
       }
   }

   // multiply
   i = expr_mult.globalMatch(data);
   while (i.hasNext()) {
       QRegularExpressionMatch match = i.next();
       mult_list << match.captured(0);
   }
   if (mult_list.length() != 0)
   {
       QString mult_sol;
       foreach (mult_sol, mult_list)
       {
           QStringList mult;
           mult << mult_sol.split('*');
           double multiply = mult[0].toDouble()*mult[1].toDouble();
           QString mult_sol_solved = QString::number(multiply, 'f', 4);
           data.replace(mult_sol,mult_sol_solved);
       }
   }


   // adding
   QString ops = "^" ;
    // change back after correction
   if (data[0] == '-' && data[1] == '-')
   {
       data.remove(0,2);
       data = '-'+data;
   }
   data.replace("--","+");
   i = expr_add.globalMatch(data);
   while (i.hasNext()) {
       QRegularExpressionMatch match = i.next();
       add_list << match.captured(0);
   }
   if (add_list.length() != 0)
   {
       QString add_sol;
       double adding =0;
       foreach (add_sol, add_list)
       {
           adding += add_sol.toDouble();
       }
       data = QString::number(adding,'f',4);
   }
   // solved
  return data;
}


// calc actions
QMap<QString, QString> Calc_actions::pow(QStringList pows_unsolved)
{
    // for displaying errors. error message/code
    QMap<QString, QString> Error;
    QStringList unsolved_prepared;
    QStringList Solved;
    // stores the final solution as QMap ("was" "became")
    QMap<QString, QString> solved_map;

    QStringList minus_cases = {"+-","--","/-","*-","^-","S-"};
    QString operations = "+-/*S";

    QString str;
    foreach (str, pows_unsolved)
    {
        QString sr = str; sr.resize(2);
        if (operations.contains(str[0]))
        {
            str.remove(0,1);
        }
        unsolved_prepared << str;
    }
    // solveing
    QString unsolved_str;
    foreach (unsolved_str, unsolved_prepared)
    {
        QStringList prep;
        prep << unsolved_str.split('^');
        double count_pow = ::pow(prep[0].toDouble(),prep[1].toDouble());
        unsolved_str = QString::number(count_pow, 'f',4);
        Solved << unsolved_str;
    }
    if (Solved.contains("nan"))
    {
        Error.insert("Error","Negative num to a non-integer power$");
        return Error;
    }

     // stores solved expressions for replacement in original expression

     if (Solved.length() == unsolved_prepared.length())
     {
         for (int i = 0; i<Solved.length(); i++)
         {
             solved_map.insert(unsolved_prepared[i], Solved[i]);
         }      
         return solved_map;
     }
     else
     {
         // you probably shoudn't ever get it
         Error.insert("Error", "Custom_error$");
         return Error;
     }
}

// almost same as pow
QMap<QString, QString> Calc_actions::sqrt(QStringList sqrts_unsolved)
{
    QMap<QString, QString> Error;
    QStringList unsolved_prepared;
    QStringList Solved;
    // stores the final solution as QMap ("was" "became")
    QMap<QString, QString> solved_map;

    QStringList minus_cases = {"+-","--","/-","*-","^-","S-"};
    QString operations = "+-/*^";

    QString str;
    foreach (str, sqrts_unsolved)
    {
        QString sr = str; sr.resize(2);        
        if (operations.contains(str[0]))
        {
            str.remove(0,1);
        }
        unsolved_prepared << str;
    }
    QString unsolved_str;
    foreach (unsolved_str, unsolved_prepared)
    {
        QStringList prep;
        prep << unsolved_str.split('S');
        double temp_devide = 1/prep[0].toDouble();
        double count_pow = ::pow(prep[1].toDouble(),temp_devide);
        unsolved_str = QString::number(count_pow, 'f',4);
        Solved << unsolved_str;
    }
    if (Solved.contains("nan"))
    {
        Error.insert("Error","Minus insude sqrt()$");
        return Error;
    }
    if (Solved.length() == unsolved_prepared.length())
    {
        for (int i = 0; i<Solved.length(); i++)
        {
            solved_map.insert(unsolved_prepared[i], Solved[i]);
        }
        return solved_map;
    }
    else
    {
        // you probably shoudn't ever get it
        Error.insert("Error", "Custom_error$");
        return Error;
    }
    return solved_map;
}
