module.exports = {
  entry: './src/Index.bs.js',
  output: {
    filename: 'Index.js',
    path: `${__dirname}/dist`,
    publicPath: '/dist/'
  }
};
