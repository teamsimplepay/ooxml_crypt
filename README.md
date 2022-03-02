# OoxmlCrypt

A Ruby library for encrypting/decrypting password-protected Microsoft Office XML (OOXML) files (e.g. .docx, .xlsx, .pptx). This is a native extension that builds on top of [the msoffice library](https://github.com/herumi/msoffice). This only supports documents encrypted (i.e. password-protected) by Office 2010 or later.

## Installation

Add this line to your application's Gemfile:

```ruby
gem 'ooxml_crypt'
```

And then execute:

    $ bundle install

Or install it yourself as:

    $ gem install ooxml_crypt

## Usage

To encrypt, you can either pass in a file or binary data:
```ruby
require "ooxml_crypt"

# pass in binary data, get binary data
encrypted_data = OoxmlCrypt.encrypt(bindata, password)

# or use file names
OoxmlCrypt.encrypt_file(filename, password, encrypted_filename)
```

The same approach holds true for decryption:
```ruby
require "ooxml_crypt"

# pass in binary data, get binary data
decrypted_data = OoxmlCrypt.decrypt(bindata, password)

# or use file names
OoxmlCrypt.decrypt_file(filename, password, decrypted_filename)
```

An exception `OoxmlCrypt::Error` will be raised in case of errors.
## Development

After checking out the repo, run `bin/setup` to install dependencies. You can also run `bin/console` for an interactive prompt that will allow you to experiment.

To install this gem onto your local machine, run `bundle exec rake install`. To release a new version, update the version number in `version.rb`, and then run `bundle exec rake release`, which will create a git tag for the version, push git commits and the created tag, and push the `.gem` file to [rubygems.org](https://rubygems.org).

## Contributing

Bug reports and pull requests are welcome on GitHub at https://github.com/teamsimplepay/ooxml_crypt.

## License

The gem is available as open source under the terms of the [MIT License](https://opensource.org/licenses/MIT).
