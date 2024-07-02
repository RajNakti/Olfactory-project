import 'dart:developer';

import 'package:flutter/material.dart';
import 'package:gasdictation/test_screen.dart';

void main() {
  runApp(const MyApp());
}

class MyApp extends StatelessWidget {
  const MyApp({super.key});

  // This widget is the root of your application.
  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      title: 'Flutter',
      theme: ThemeData(
        colorScheme: ColorScheme.fromSeed(
            seedColor: const Color.fromARGB(255, 67, 126, 150)),
        useMaterial3: true,
      ),
      home: const MyHomePage(title: 'AI'),
    );
  }
}

class MyHomePage extends StatefulWidget {
  const MyHomePage({super.key, required this.title});
  final String title;

  @override
  State<MyHomePage> createState() => _MyHomePageState();
}

class _MyHomePageState extends State<MyHomePage> {
  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        backgroundColor: Theme.of(context).colorScheme.inversePrimary,
        title: Text(widget.title),
      ),
      body: Column(
        crossAxisAlignment: CrossAxisAlignment.start,
        children: [
          const Padding(
            padding: EdgeInsets.all(8.0),
            child: Text(
              'Gas Detection',
              style: TextStyle(
                fontSize: 32,
                fontWeight: FontWeight.bold,
              ),
            ),
          ),
          Expanded(
            child: Align(
                alignment: Alignment.center,
                child: Column(
                  mainAxisAlignment: MainAxisAlignment.center,
                  children: [
                    ElevatedButton(
                      style: ElevatedButton.styleFrom(
                          backgroundColor: Colors.yellow,
                          foregroundColor: Colors.black,
                          minimumSize: const Size(250, 50),
                          shape: RoundedRectangleBorder(
                            borderRadius: BorderRadius.circular(10),
                          )),
                      onPressed: () {
                        log('Banana');
                        Navigator.push(
                          context,
                          MaterialPageRoute(
                            builder: (context) => const TestScreen(
                                title: "Banana",
                                img: "assets/banana.png",
                                color: Colors.yellow),
                          ),
                        );
                      },
                      child:
                          const Text('Banana', style: TextStyle(fontSize: 24)),
                      // icon: Image.asset('assets/banana.png', width: 40, height: 40),
                    ),
                    const SizedBox(height: 40),
                    ElevatedButton(
                        style: ElevatedButton.styleFrom(
                            backgroundColor: Colors.brown,
                            foregroundColor: Colors.white,
                            minimumSize: const Size(250, 50),
                            shape: RoundedRectangleBorder(
                              borderRadius: BorderRadius.circular(10),
                            )),
                        onPressed: () {
                          log('Potato');
                          Navigator.push(
                            context,
                            MaterialPageRoute(
                                builder: (context) => const TestScreen(
                                    title: "Potato",
                                    img: "assets/potato.png",
                                    color: Colors.brown)),
                          );
                        },
                        child: const Text('Potato',
                            style: TextStyle(fontSize: 24))),
                    const SizedBox(height: 40),
                    ElevatedButton(
                        style: ElevatedButton.styleFrom(
                            backgroundColor: Colors.red,
                            foregroundColor: Colors.white,
                            minimumSize: const Size(250, 50),
                            shape: RoundedRectangleBorder(
                              borderRadius: BorderRadius.circular(10),
                            )),
                        onPressed: () {
                          log('Tomato');
                          Navigator.push(
                            context,
                            MaterialPageRoute(
                                builder: (context) => const TestScreen(
                                    title: "Tomato",
                                    img: "assets/tomato.png",
                                    color: Colors.red)),
                          );
                        },
                        child: const Text('Tomato',
                            style: TextStyle(fontSize: 24))),
                  ],
                )),
          )
        ],
      ),
    );
  }
}
