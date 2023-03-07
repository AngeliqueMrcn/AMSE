import 'dart:math';

import 'package:flutter/material.dart';

void main() => runApp(MyApp());

class MyApp extends StatelessWidget {
  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      title: 'Puzzle Game Demo',
      home: Scaffold(
        appBar: AppBar(
          title: Text('Puzzle Game Demo'),
        ),
        body: PuzzleGame(),
      ),
    );
  }
}

class PuzzleGame extends StatefulWidget {
  @override
  _PuzzleGameState createState() => _PuzzleGameState();
}

class _PuzzleGameState extends State<PuzzleGame> {
  final int _rowCount = 3;
  final int _columnCount = 3;

  List<Widget> _tiles = [];
  int? _emptyTileIndex;

  @override
  void initState() {
    super.initState();
    _tiles = _createTiles();
    _shuffleTiles();
  }

  List<Widget> _createTiles() {
    List<Widget> tiles = [];
    for (int i = 0; i < _rowCount * _columnCount - 1; i++) {
      tiles.add(_Tile(index: i));
    }
    tiles.add(Container()); // Empty tile
    return tiles;
  }

  void _shuffleTiles() {
    int n = _tiles.length;
    Random random = Random();
    for (int i = n - 1; i > 0; i--) {
      int j = random.nextInt(i + 1);
      if (i == _tiles.length - 1) {
        _emptyTileIndex = j;
      } else if (j == _tiles.length - 1) {
        _emptyTileIndex = i;
      }
      Widget temp = _tiles[i];
      _tiles[i] = _tiles[j];
      _tiles[j] = temp;
    }
  }

  void _swapTiles(int index) {
    if (_canMoveTile(index)) {
      setState(() {
        Widget temp = _tiles[index];
        _tiles[index] = _tiles[_emptyTileIndex!];
        _tiles[_emptyTileIndex!] = temp;
        _emptyTileIndex = index;
      });
    }
  }

  bool _canMoveTile(int index) {
    int emptyRow = _emptyTileIndex! ~/ _columnCount;
    int emptyColumn = _emptyTileIndex! % _columnCount;
    int row = index ~/ _columnCount;
    int column = index % _columnCount;
    return (emptyRow == row && (emptyColumn - column).abs() == 1) ||
        (emptyColumn == column && (emptyRow - row).abs() == 1);
  }

  @override
  Widget build(BuildContext context) {
    return GridView.count(
      crossAxisCount: _columnCount,
      children: List.generate(_tiles.length, (index) {
        return GestureDetector(
          onTap: () => _swapTiles(index),
          child: _tiles[index],
        );
      }),
    );
  }
}

class _Tile extends StatelessWidget {
  final int index;

  _Tile({required this.index});

  @override
  Widget build(BuildContext context) {
    return Image.asset(
      'assets/images/0-Star-Wars-memes.jpeg',
    );
  }
}