module.exports = function(grunt) {
  grunt.initConfig({
    pkg: grunt.file.readJSON('package.json'),
    jshint: {
      files: ['Gruntfile.js', 'src/**/*.js', 'test/**/*.js'],
      options: {
        esversion: 6,
        globals: {
          console: true,
          module: true,
          node: true
        }
      }
    },
    watch: {
      files: ['main.js', 'src/**/*.c*', 'src/**/*.h*','test/**/*.js'],
      tasks: ['gyp', 'jshint', 'simplemocha']
    },
    simplemocha: {
      options: {
        fullTrace: true
      },
      all: {
        src: ['test/**/*.js', '**/*.spec.js']
      }
    },
    gyp: {
      addon: {}
    }
  });

  grunt.loadNpmTasks('grunt-contrib-jshint');
  grunt.loadNpmTasks('grunt-contrib-watch');
  grunt.loadNpmTasks('grunt-simple-mocha');
  grunt.loadNpmTasks('grunt-node-gyp');

  grunt.registerTask('test', ['jshint', 'simplemocha']);
  
  return grunt.registerTask('default', ['gyp', 'jshint', 'simplemocha']);
};
