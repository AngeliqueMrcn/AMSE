import 'package:flutter/material.dart';

// import 'util.dart';
import 'exo1.dart' as exo1;
import 'exo2.dart' as exo2;
import 'exo3.dart' as exo3;
import 'exo4.dart' as exo4;
import 'exo5a.dart' as exo5a;
import 'exo5b.dart' as exo5b;
import 'exo6.dart' as exo6;

void main() => runApp(MyApp());

class MyApp extends StatelessWidget {
  @override
  Widget build(BuildContext context) {
    return MaterialApp(home: MenuPage());
  }
}

class Exo {
  final String? title;
  final String? subtitle;
  final WidgetBuilder? buildFunc;

  const Exo({@required this.title, this.subtitle, @required this.buildFunc});
}

List exos = [
  Exo(
      title: 'Exercice 1',
      subtitle: 'Afficher une image',
      buildFunc: (context) => exo1.DisplayImageWidget()),
  Exo(
      title: 'Exercice 2',
      subtitle: 'Transformer une image',
      buildFunc: (context) => exo2.DisplayImageWidget()),
  Exo(
      title: 'Exercice 3',
      subtitle: 'Menu',
      buildFunc: (context) => exo3.DisplayImageWidget()),
  Exo(
      title: 'Exercice 4',
      subtitle: 'Affichage dune tuile',
      buildFunc: (context) => exo4.DisplayImageWidget()),
  Exo(
      title: 'Exercice 5a',
      subtitle: 'Génération du plateau de tuiles',
      buildFunc: (context) => exo5a.PositionedTiles()),
      /*
  Exo(
      title: 'Exercice 5b',
      subtitle: 'Génération du plateau de tuiles avec image',
      buildFunc: (context) => exo5b.PositionedTiles()),
      */
  Exo(
      title: 'Exercice 6',
      subtitle: 'Animation dune tuile',
      buildFunc: (context) => exo6.PositionedTiles()),
];

class MenuPage extends StatelessWidget {
  @override
  Widget build(BuildContext context) {
    return Scaffold(
        appBar: AppBar(
          title: Text('TP2'),
        ),
        body: ListView.builder(
            itemCount: exos.length,
            itemBuilder: (context, index) {
              var exo = exos[index];
              return Card(
                  child: ListTile(
                      title: Text(exo.title),
                      subtitle: Text(exo.subtitle),
                      trailing: Icon(Icons.play_arrow_rounded),
                      onTap: () {
                        Navigator.push(
                          context,
                          MaterialPageRoute(builder: exo.buildFunc),
                        );
                      }));
            }));
  }
}
