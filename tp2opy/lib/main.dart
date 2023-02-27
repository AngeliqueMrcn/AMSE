import 'package:flutter/material.dart';

void main() => runApp(MyApp());

class MyApp extends StatelessWidget {
  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      title: 'Plateau de tuiles',
      home: Scaffold(
        appBar: AppBar(
          title: Text('Plateau de tuiles'),
        ),
        body: GridView.count(
          crossAxisCount: 4,
          children: List.generate(
            24,
            (index) {
              return Container(
                color: Colors.blueGrey[index % 8 * 100],
              );
            },
          ),
        ),
      ),
    );
  }
}
