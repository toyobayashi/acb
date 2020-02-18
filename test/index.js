const crypto = require('crypto')
const fs = require('fs')
const path = require('path')

function md5 (p) {
  return crypto.createHash('md5').update(fs.readFileSync(p)).digest('hex')
}

const dir = path.join(__dirname, '../build/win32/Debug')

const lsc = fs.readdirSync(path.join(dir, 'sub/solo'))
const lsc2 = fs.readdirSync(path.join(dir, 'sub/100071'))

for (let i = 0; i < lsc.length; i++) {
  console.log(lsc[i])
  const cmd5 = md5(path.join(dir, 'sub/solo', lsc[i]))
  const jsmd5 = md5(path.join(dir, '_acb_solo.acb', lsc[i]))
  console.log(`C: ${cmd5}, JS: ${jsmd5}`)
  if (cmd5 !== jsmd5) {
    process.exit(1)
  }
}

for (let i = 0; i < lsc2.length; i++) {
  console.log(lsc2[i])
  const cmd5 = md5(path.join(dir, 'sub/100071', lsc2[i]))
  const jsmd5 = md5(path.join(dir, '_acb_100071.acb', lsc2[i]))
  console.log(`C: ${cmd5}, JS: ${jsmd5}`)
  if (cmd5 !== jsmd5) {
    process.exit(1)
  }
}
